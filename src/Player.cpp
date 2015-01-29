#include "Player.h"

Player::Player()
{
    m_type = "Player";
    m_speed = 140.f;
    m_gravity = 200.f;
    m_jump_max_velocity = 500.f;
    m_jump_deceleration = 10.f;
    m_side = 1;
    m_jumping = false;
    m_canJump = false;
    m_frameToJump = 0;
    m_requiredFramesToJump = 5;

    m_texture.loadFromFile("assets/player.png");

    m_walkingAnimationRight.setSpriteSheet(m_texture);
    m_walkingAnimationRight.addFrame(IntRect(32, 0, 32, 48));
    m_walkingAnimationRight.addFrame(IntRect(64, 0, 32, 48));
    m_walkingAnimationRight.addFrame(IntRect(96, 0, 32, 48));
    m_walkingAnimationRight.addFrame(IntRect(128, 0, 32, 48));

    m_currentAnimation = &m_walkingAnimationRight;

    m_animatedSprite.setFrameTime(seconds(0.2));

    m_animatedSprite.setOrigin(16, 24);
    m_animatedSprite.setPosition(64, 0);
}

void Player::update(Time frameTime)
{
    m_oldPosition = m_animatedSprite.getPosition();
    Vector2f movement(0.f, m_gravity);
    bool noKeyWasPressed = true;

    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        m_currentAnimation = &m_walkingAnimationRight;
        m_side = -1;
        movement.x -= m_speed;
        noKeyWasPressed = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        m_currentAnimation = &m_walkingAnimationRight;
        m_side = 1;
        movement.x += m_speed;
        noKeyWasPressed = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && !m_jumping && m_canJump)
    {
        m_jumping = true;
        m_jump_velocity = m_jump_max_velocity;
    }

    if(m_jumping)
    {
        movement.y -= m_jump_velocity;
        if(m_jump_velocity - m_jump_deceleration > 0)
        {
            m_jump_velocity -= m_jump_deceleration;
        }
        else
        {
            m_jump_velocity = 0;
        }
    }

    m_canJump = false;

    if (noKeyWasPressed)
    {
        m_animatedSprite.stop();
    }

    m_animatedSprite.setScale(1.f * m_side, 1.f);

    m_animatedSprite.move(movement * frameTime.asSeconds());

    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.update(frameTime);
}

void Player::draw(RenderWindow& window)
{
    window.draw(m_animatedSprite);
}

FloatRect Player::getBoundBox()
{
    return m_animatedSprite.getGlobalBounds();
}

void Player::collide(Entity* entity)
{
    Vector2f position = m_animatedSprite.getPosition();
    Vector2f mouvement = Vector2f(position.x - m_oldPosition.x, position.y - m_oldPosition.y);
    float right = m_animatedSprite.getGlobalBounds().left + m_animatedSprite.getGlobalBounds().width;
    float bottom = m_animatedSprite.getGlobalBounds().top + m_animatedSprite.getGlobalBounds().height;
    float e_right = entity->getBoundBox().left + entity->getBoundBox().width;
    float e_bottom = entity->getBoundBox().top + entity->getBoundBox().height;
    Vector2f overlap;
    int xfix = 3;

    if(right/2 < e_right /2)
    {
        overlap.x = (right - entity->getBoundBox().left) * -1;
    }
    else
    {
        overlap.x = e_right - m_animatedSprite.getGlobalBounds().left;
    }

    // multi collisions ?

    if(entity->m_type == "Slope")
    {
        Slope* slope = dynamic_cast<Slope*>(entity);
        float x;
        if(right/2 < e_right/2)
        {
            x = right - entity->getBoundBox().left;
        }
        else
        {
            x = e_right - m_animatedSprite.getGlobalBounds().left;
        }
        if(x < 0)
            x = 0;
        if(x > MapManager::m_gridSize)
            x = MapManager::m_gridSize;

        cout << "collinding with a slope of angle : " << slope->m_angle.x << " " << slope->m_angle.y << endl;
        cout << "Relative origin x to the tile : " << x << endl;
        cout << "Y position by slope vector : " << x * slope->m_angle.x << endl;
        cout << "Current y : " << m_animatedSprite.getPosition().y << endl;
        cout << "New y : " << e_bottom - x * slope->m_angle.x - m_animatedSprite.getGlobalBounds().height/2 - slope->m_angle.y << endl;

        // fix left half slopes

        // add base y (half tile ?) slope starting at custom height
        // avoid sticky mod (as soon as player enter in collision, he is swaped to y pos, do ony if player.y > block.y
        // allow jump on slope

        m_animatedSprite.setPosition(position.x, e_bottom - x * slope->m_angle.x - m_animatedSprite.getGlobalBounds().height/2 - slope->m_angle.y);
        overlap.y = 0;
    }
    else
    {
        if(bottom/2 < e_bottom/2)
        {
            overlap.y = (bottom - entity->getBoundBox().top) * -1;
        }
        else
        {
            overlap.y = e_bottom - m_animatedSprite.getGlobalBounds().top;
        }
    }

    if(fabs(overlap.x) + xfix < fabs(overlap.y))
    {
        m_animatedSprite.move(overlap.x, 0);
    }
    else
    {
        m_animatedSprite.move(0, overlap.y);
        if(mouvement.y < 0)
        {
            m_jump_velocity = 0;
        }
        else if(m_animatedSprite.getGlobalBounds().top + m_animatedSprite.getGlobalBounds().height == entity->getBoundBox().top)
        {
            m_jumping = false;
            ++m_frameToJump;
            if(m_frameToJump == m_requiredFramesToJump)
            {
                m_frameToJump = 0;
                m_canJump = true;
            }
        }
    }
}


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

    int margin = 8;

    FloatRect topSide = FloatRect(
                                  entity->getBoundBox().left,
                                  entity->getBoundBox().top,
                                  entity->getBoundBox().width,
                                  margin
                                  );
    FloatRect downSide = FloatRect(
                                   entity->getBoundBox().left,
                                   entity->getBoundBox().top + entity->getBoundBox().height - margin,
                                   entity->getBoundBox().width,
                                   margin
                                   );
    FloatRect leftSide = FloatRect(
                                   entity->getBoundBox().left,
                                   entity->getBoundBox().top + margin,
                                   margin,
                                   entity->getBoundBox().height - margin * 2
                                   );
    FloatRect rightSide = FloatRect(
                                   entity->getBoundBox().left + entity->getBoundBox().width - margin,
                                   entity->getBoundBox().top + margin,
                                   margin,
                                   entity->getBoundBox().height - margin * 2
                                   );
    if(mouvement.x < 0 && rightSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(entity->getBoundBox().left + entity->getBoundBox().width + m_animatedSprite.getGlobalBounds().width / 2, position.y);
    }

    if(mouvement.x > 0 && leftSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(entity->getBoundBox().left - m_animatedSprite.getGlobalBounds().width / 2, position.y);
    }

    if(entity->m_type == "Slope")
    {
        Slope* slope = dynamic_cast<Slope*>(entity);
        float x = m_animatedSprite.getPosition().x - entity->getBoundBox().left;
        if(x < 0)
            x = 0;
        if(x > MapManager::m_gridSize)
            x = MapManager::m_gridSize;

        if(slope->m_angle.x == -1)
            x -= MapManager::m_gridSize;

        float newY = entity->getBoundBox().top + entity->getBoundBox().height - x * slope->m_angle.x - m_animatedSprite.getGlobalBounds().height / 2;

        cout << "collinding with a slope of angle : " << slope->m_angle.x << " " << slope->m_angle.y << endl;
        cout << "Relative origin x to the tile : " << x << endl;
        cout << "Y position by slope vector : " << x * slope->m_angle.x << endl;
        cout << "Current y : " << m_animatedSprite.getPosition().y << endl;
        cout << "New y : " << newY << endl;

        if(newY < m_animatedSprite.getPosition().y)
            m_animatedSprite.setPosition(position.x, newY);
    }
    else
    {
        if(mouvement.y > 0 && topSide.intersects(this->getBoundBox()))
        {
            m_animatedSprite.setPosition(position.x, entity->getBoundBox().top - m_animatedSprite.getGlobalBounds().height / 2);
            m_jumping = false;
            m_canJump = true;
        }

        if(mouvement.y < 0 && downSide.intersects(this->getBoundBox()))
        {
            m_animatedSprite.setPosition(position.x, entity->getBoundBox().top + entity->getBoundBox().height + m_animatedSprite.getGlobalBounds().height / 2);
            m_jump_velocity = 0;
        }
    }
}


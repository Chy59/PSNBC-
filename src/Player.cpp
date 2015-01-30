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
            m_jumping = false;
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

    this->doCollisions();
}

void Player::draw(RenderWindow& window)
{
    window.draw(m_animatedSprite);
}

FloatRect Player::getBoundBox()
{
    return m_animatedSprite.getGlobalBounds();
}

void Player::doCollisions()
{
    vector<Entity*> entities = EntityManager::getInstance().getEntities();
    for(int i = 0, len = entities.size(); i < len; ++i)
    {
        if(entities[i]->m_hasCollisions)
        {
            if(CollisionManager::getInstance().collideAABB(entities[i]->getBoundBox(), this->getBoundBox()))
            {
                this->collide(entities[i]);
            }
        }
    }
}

void Player::collide(Entity* entity)
{
    float right = this->right();
    float bottom = this->bottom();
    float left = this->left();
    float top = this->top();
    float e_right = entity->right();
    float e_bottom = entity->bottom();
    float e_top = entity->top();
    float e_left = entity->left();
    Vector2f overlap = Vector2f(0, 0);
    int x_fix = 4;
    bool slope_collision = false;

    if(right/2 < e_right/2)
    {
        overlap.x = (right - e_left) * -1;
    }
    else
    {
        overlap.x = e_right - left;
    }

    if(entity->m_type == "Slope")
    {
        slope_collision = true;
        Slope* slope = dynamic_cast<Slope*>(entity);
        float x;

        if(slope->m_inverted)
        {
            if(slope->m_angle >= 0)
                x = right - e_left;
            else
                x = e_right - left;
        }
        else
        {
            if(slope->m_angle < 0)
                x = right - e_left;
            else
                x = e_right - left;
        }

        if(x < 0)
            x = 0;
        if(x > MapManager::m_gridSize)
            x = MapManager::m_gridSize;

        if(slope->m_inverted)
        {
            float newY = e_top + x * fabs(slope->m_angle) + m_animatedSprite.getGlobalBounds().height/2 + slope->m_base_y;
            if(newY > m_animatedSprite.getPosition().y)
            {
                overlap.y = newY - m_animatedSprite.getPosition().y;
                m_jump_velocity = 0;
                m_jumping = false;
            }

        }
        else
        {
            float newY = e_bottom - x * fabs(slope->m_angle) - m_animatedSprite.getGlobalBounds().height/2 - slope->m_base_y;
            if(newY < m_animatedSprite.getPosition().y)
            {
                overlap.y = newY - m_animatedSprite.getPosition().y;
                m_canJump = true;
            }
        }
    }
    else
    {
        if(bottom/2 < e_bottom/2)
        {
            overlap.y = (bottom - e_top) * -1;
        }
        else
        {
            overlap.y = e_bottom - top;
        }
    }

    if(fabs(overlap.x) + x_fix < fabs(overlap.y))
    {
        m_animatedSprite.move(overlap.x, 0);
    }
    else
    {
        m_animatedSprite.move(0, overlap.y);
        if(this->top() == e_bottom)
        {
            m_jump_velocity = 0;
            m_jumping = false;
        }
        if(this->bottom() == e_top && !slope_collision)
        {
            m_canJump = true;
        }
    }
}


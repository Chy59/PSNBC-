#include "Player.h"

Player::Player()
{
    m_speed = 140.f;
    m_gravity = 200.f;
    m_jump_max_velocity = 500.f;
    m_jump_deceleration = 10.f;
    m_side = 1;

    m_texture.loadFromFile("player.png");

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

    if (Keyboard::isKeyPressed(Keyboard::Up) && !m_jumping)
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

void Player::collide(Entity* entitiy)
{
    Vector2f position = m_animatedSprite.getPosition();
    Vector2f mouvement = Vector2f(position.x - m_oldPosition.x, position.y - m_oldPosition.y);

    int margin = 4;

    FloatRect topSide = FloatRect(
                                  entitiy->getBoundBox().left,
                                  entitiy->getBoundBox().top,
                                  entitiy->getBoundBox().width,
                                  margin
                                  );
    FloatRect downSide = FloatRect(
                                   entitiy->getBoundBox().left,
                                   entitiy->getBoundBox().top + entitiy->getBoundBox().height - margin,
                                   entitiy->getBoundBox().width,
                                   margin
                                   );
    FloatRect leftSide = FloatRect(
                                   entitiy->getBoundBox().left,
                                   entitiy->getBoundBox().top + margin,
                                   margin,
                                   entitiy->getBoundBox().height - margin * 2
                                   );
    FloatRect rightSide = FloatRect(
                                   entitiy->getBoundBox().left + entitiy->getBoundBox().width - margin,
                                   entitiy->getBoundBox().top + margin,
                                   margin,
                                   entitiy->getBoundBox().height - margin * 2
                                   );
    if(mouvement.x < 0 && rightSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(entitiy->getBoundBox().left + entitiy->getBoundBox().width + m_animatedSprite.getGlobalBounds().width / 2, position.y);
    }

    if(mouvement.x > 0 && leftSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(entitiy->getBoundBox().left - m_animatedSprite.getGlobalBounds().width / 2, position.y);
    }

    if(mouvement.y > 0 && topSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(position.x, entitiy->getBoundBox().top - m_animatedSprite.getGlobalBounds().height / 2);
        m_jumping = false;
    }

    if(mouvement.y < 0 && downSide.intersects(this->getBoundBox()))
    {
        m_animatedSprite.setPosition(position.x, entitiy->getBoundBox().top + entitiy->getBoundBox().height + m_animatedSprite.getGlobalBounds().height / 2);
        m_jump_velocity = 0;
    }
}


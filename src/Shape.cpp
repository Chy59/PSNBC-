#include "Shape.h"

MyShape::MyShape(float x, float y)
{
    m_texture.loadFromFile("player.png");

    m_walkingAnimationDown.setSpriteSheet(m_texture);
    m_walkingAnimationDown.addFrame(IntRect(32, 0, 32, 32));
    m_walkingAnimationDown.addFrame(IntRect(64, 0, 32, 32));
    m_walkingAnimationDown.addFrame(IntRect(32, 0, 32, 32));
    m_walkingAnimationDown.addFrame(IntRect( 0, 0, 32, 32));

    m_currentAnimation = &m_walkingAnimationDown;

    m_animatedSprite.setFrameTime(seconds(0.2));
    m_animatedSprite.setPosition(x, y);
}

void MyShape::update(Time frameTime)
{
    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.update(frameTime);
}

void MyShape::draw(RenderWindow& window)
{
    window.draw(m_animatedSprite);
}

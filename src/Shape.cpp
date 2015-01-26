#include "Shape.h"

MyShape::MyShape(float x, float y)
{
    texture.loadFromFile("player.png");

    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(IntRect( 0, 0, 32, 32));

    currentAnimation = &walkingAnimationDown;

    animatedSprite.setFrameTime(seconds(0.2));
    animatedSprite.setPosition(x, y);
}

void MyShape::update(Time frameTime)
{
    animatedSprite.play(*currentAnimation);
    animatedSprite.update(frameTime);
}

void MyShape::draw(RenderWindow& window)
{
    window.draw(animatedSprite);
}

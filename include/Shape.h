#ifndef SHAPE_H
#define SHAPE_H

#include <Entity.h>

class MyShape : public Entity
{
    public:
        MyShape(float x, float y);
        virtual void update(Time frameTime);
        virtual void draw(RenderWindow& window);
    protected:
    private:
        Texture texture;
        Animation walkingAnimationDown;
        Animation* currentAnimation;
        AnimatedSprite animatedSprite;
};

#endif // SHAPE_H

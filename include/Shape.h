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
        Texture m_texture;
        Animation m_walkingAnimationDown;
        Animation* m_currentAnimation;
        AnimatedSprite m_animatedSprite;
};

#endif // SHAPE_H

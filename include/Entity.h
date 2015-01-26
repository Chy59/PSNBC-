#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <AnimatedSprite.hpp>

using namespace sf;

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        virtual void update(Time frameTime);
        virtual void draw(RenderWindow& window);
        bool destroy;
    protected:
    private:
};

#endif // ENTITY_H

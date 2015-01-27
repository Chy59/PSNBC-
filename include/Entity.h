#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <AnimatedSprite.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        virtual void update(Time frameTime);
        virtual void draw(RenderWindow& window);
        virtual FloatRect getBoundBox();
        bool m_destroy;
        bool m_hasCollisions;
    protected:
    private:
};

#endif // ENTITY_H

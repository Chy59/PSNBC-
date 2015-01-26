#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>

using namespace sf;

class Game
{
    public:
        Game();
        void update();
    protected:
    private:
        RenderWindow window;
        EntityManager entityManager;
        Clock frameClock;
};

#endif // GAME_H

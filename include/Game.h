#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>
#include <MapManager.h>

using namespace sf;

class Game
{
    public:
        Game();
        void update();
        EntityManager getEntityManager();
    protected:
    private:
        RenderWindow window;
        EntityManager entityManager;
        MapManager mapManager;
        Clock frameClock;
};

#endif // GAME_H

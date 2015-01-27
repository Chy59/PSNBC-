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
    protected:
    private:
        RenderWindow m_window;
        EntityManager m_entityManager;
        MapManager* m_mapManager;
        Clock m_frameClock;
};

#endif // GAME_H

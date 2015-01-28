#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>
#include <MapManager.h>
#include <CollisionManager.h>
#include <Player.h>

using namespace sf;

class Game
{
    public:
        Game();
        void update();
    protected:
    private:
        RenderWindow m_window;
        Clock m_frameClock;
        Player* m_player;
};

#endif // GAME_H

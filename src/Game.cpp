#include "Game.h"

Game::Game()
{
    m_window.create(VideoMode(800, 600), "PSNBC");
    m_window.setFramerateLimit(60);

    m_player = new Player();
    EntityManager::getInstance().addEntity(m_player);

    MapManager::getInstance().loadMap("maps/map1.json");
}

void Game::update()
{
    while(m_window.isOpen())
    {
        Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                m_window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
            m_window.close();

        Time frameTime = m_frameClock.restart();

        EntityManager::getInstance().beforeDraw(frameTime);

        m_window.clear();

        EntityManager::getInstance().draw(m_window);

        m_window.display();

        EntityManager::getInstance().afterDraw();
    }

    AssetsManager::getInstance().close();
}

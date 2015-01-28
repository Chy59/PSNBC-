#include "Game.h"

Game::Game()
{
    m_window.create(VideoMode(800, 600), "PSNBC");
    m_window.setFramerateLimit(60);

    m_player = new Player();
    EntityManager::Instance().addEntity(m_player);

    MapManager::Instance().loadMap("maps/1.txt");
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

        EntityManager::Instance().beforeDraw(frameTime);

        CollisionManager::Instance().update(m_player);

        m_window.clear();

        EntityManager::Instance().draw(m_window);

        m_window.display();

        EntityManager::Instance().afterDraw();
    }
}

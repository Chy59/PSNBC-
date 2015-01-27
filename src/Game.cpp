#include "Game.h"

#include<Shape.h>

Game::Game()
{
    m_window.create(VideoMode(800, 600), "PSNBC");
    m_window.setFramerateLimit(60);

    MyShape* shape = new MyShape(0, 0);
    m_entityManager.addEntity(shape);

    m_mapManager = new MapManager(&m_entityManager);
    m_mapManager->generateMap();
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

        m_entityManager.beforeDraw(frameTime);

        m_window.clear();

        m_entityManager.draw(m_window);

        m_window.display();

        m_entityManager.afterDraw();
    }
}

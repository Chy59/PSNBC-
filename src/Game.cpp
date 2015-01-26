#include "Game.h"

Game::Game()
{
    window.create(VideoMode(800, 600), "PSNBC");
    window.setFramerateLimit(60);

    entityManager.addEntity();
}

void Game::update()
{
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        Time frameTime = frameClock.restart();

        entityManager.beforeDraw(frameTime);

        window.clear();

        entityManager.draw(window);

        window.display();

        entityManager.afterDraw();
    }
}

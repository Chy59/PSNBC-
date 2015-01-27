#include "MapManager.h"

MapManager::MapManager(EntityManager* entityManager) :
    m_entityManager(entityManager)
{
    m_gridSize = 32;
    m_texture.loadFromFile("tileset-platformer.png");
}

void MapManager::generateMap()
{
    this->addTile(0, 10, 0);
    this->addTile(1, 10, 1);
    this->addTile(2, 10, 22);
    this->addTile(3, 10, 1);
    this->addTile(4, 10, 2);
    this->addTile(2, 11, 22);
    this->addTile(2, 9, 22);
    this->addTile(2, 8, 16);
}

void MapManager::addTile(float x, float y, int tileId)
{
    Vector2u tile = this->getTileById(tileId);
    m_entityManager->addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
}

Vector2u MapManager::getTileById(int tileId)
{
    float columns = m_texture.getSize().x / m_gridSize;

    double y = 0;
    double x = 0;

    if(tileId > 0)
        x = modf(tileId / columns, &y) * columns;

    return Vector2u(x, y);
}

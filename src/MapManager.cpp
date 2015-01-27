#include "MapManager.h"

MapManager::MapManager(EntityManager* entityManager) :
    m_entityManager(entityManager)
{
    m_gridSize = 16;
    m_texture.loadFromFile("tileset.png");
}

void MapManager::generateMap()
{
    this->addTile(0, 2, 4);
    this->addTile(1, 2, 7);
    this->addTile(2, 2, 16);
    this->addTile(3, 2, 19);
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
    int x = 0;

    if(tileId > 0)
        x = modf(tileId / columns, &y) * m_gridSize;

    return Vector2u(x, y);
}

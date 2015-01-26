#include "MapManager.h"

MapManager::MapManager()
{
    gridSize = 16;
    texture.loadFromFile("tileset.png");
}

void MapManager::setEntityManager(EntityManager* em)
{
    entityManager = em;
}

void MapManager::generateMap()
{
    this->addTile(3, 4, 0, 0);
    this->addTile(4, 4, 1, 0);
    this->addTile(5, 4, 2, 0);
}

void MapManager::addTile(float x, float y, int tileX, int tileY)
{
    entityManager->addEntity(new Tile(x, y, tileX, tileY, texture, gridSize));
}

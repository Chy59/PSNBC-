#include "MapManager.h"

MapManager::MapManager(EntityManager* entityManager) :
    m_entityManager(entityManager)
{
    m_gridSize = 32;
    m_texture.loadFromFile("assets/tileset-platformer.png");
}

void MapManager::generateMap(const char* mapName)
{
    ifstream mapFile(mapName);

    int columns;
    int currentColumn = 0;
    int currentRow = 0;

    if(mapFile.is_open())
    {
        mapFile >> columns;
        --columns;

        while(!mapFile.eof())
        {
            int line;
            mapFile >> line;

            if(line > 0)
            {
                --line;
                this->addTile(currentColumn, currentRow, line);
            }

            if(currentColumn < columns)
                ++currentColumn;
            else
            {
                currentColumn = 0;
                ++currentRow;
            }
        }
        mapFile.close();
    }
}

void MapManager::addTile(float x, float y, int tileId)
{
    Vector2f tile = this->getTileById(tileId);
    m_entityManager->addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
}

Vector2f MapManager::getTileById(int tileId)
{
    float columns = m_texture.getSize().x / m_gridSize;

    double y = 0;
    double x = 0;

    if(tileId > 0)
        x = modf(tileId / columns, &y) * columns;

    return Vector2f(x, y);
}

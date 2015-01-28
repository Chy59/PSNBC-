#include "MapManager.h"

int MapManager::m_gridSize;
Texture MapManager::m_texture;
MapManager MapManager::m_instance = MapManager();

MapManager& MapManager::Instance()
{
    return m_instance;
}

MapManager::MapManager()
{
    m_gridSize = 32;
    m_texture.loadFromFile("assets/tileset-platformer.png");
}

void MapManager::loadMap(const char* mapName)
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
                MapManager::Instance().addTile(currentColumn, currentRow, line);
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
    Vector2f tile = MapManager::Instance().getTileById(tileId);
    EntityManager::Instance().addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
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

void MapManager::unloadMap()
{
    EntityManager::Instance().clearByType("Tile");
}

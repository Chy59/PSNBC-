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

    MapManager::Instance().addTile(2, 6, 25);
    MapManager::Instance().addTile(3, 6, 26);
    MapManager::Instance().addTile(4, 6, 27);
}

void MapManager::addTile(float x, float y, int tileId)
{
    Vector2f tile = MapManager::Instance().getTileById(tileId);
    Vector2f angle = MapManager::Instance().getTileAngle(tileId);
    if(angle == Vector2f(0, 0))
        EntityManager::Instance().addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
    else
        EntityManager::Instance().addEntity(new Slope(x, y, tile.x, tile.y, m_texture, m_gridSize, angle));
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

Vector2f MapManager::getTileAngle(int tileId)
{
    if(tileId == 25)
        return Vector2f(1, 1);
    if(tileId == 27)
        return Vector2f(-1, 1);
    return Vector2f(0, 0);
}

void MapManager::unloadMap()
{
    EntityManager::Instance().clearByType("Tile");
}

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
    float angle = MapManager::Instance().getTileAngle(tileId);
    int base_y = MapManager::Instance().getTileBaseY(tileId);
    if(angle == 0 && base_y == 0)
        EntityManager::Instance().addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
    else
        EntityManager::Instance().addEntity(new Slope(x, y, tile.x, tile.y, m_texture, m_gridSize, angle, base_y, MapManager::Instance().getTileSide(tileId)));
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

float MapManager::getTileAngle(int tileId)
{
    if(tileId == 25)
        return -1;
    if(tileId == 27)
        return 1;
    if(tileId == 96)
        return -0.5;
    if(tileId == 97)
        return -0.5;
    if(tileId == 98)
        return 0.5;
    if(tileId == 99)
        return 0.5;
    if(tileId == 100)
        return 0;
     if(tileId == 101)
        return 1;
     if(tileId == 102)
        return 0.5;
     if(tileId == 103)
        return 0.5;
     if(tileId == 104)
        return -0.5;
     if(tileId == 105)
        return -0.5;
     if(tileId == 106)
        return 0;
     if(tileId == 107)
        return -1;
    return 0;
}

int MapManager::getTileBaseY(int tileId)
{
    if(tileId == 25)
        return 0;
    if(tileId == 27)
        return 0;
    if(tileId == 96)
        return 0;
    if(tileId == 97)
        return 16;
    if(tileId == 98)
        return 16;
    if(tileId == 99)
        return 0;
    if(tileId == 100)
        return 16;
    if(tileId == 101)
        return 0;
    if(tileId == 102)
        return 0;
    if(tileId == 103)
        return 16;
    if(tileId == 104)
        return 16;
    if(tileId == 105)
        return 0;
    if(tileId == 106)
        return 16;
    if(tileId == 107)
        return 0;
    return 0;
}

bool MapManager::getTileSide(int tileId)
{
    if(tileId == 25)
        return false;
    if(tileId == 27)
        return false;
    if(tileId == 96)
        return false;
    if(tileId == 97)
        return false;
    if(tileId == 98)
        return false;
    if(tileId == 99)
        return false;
    if(tileId == 100)
        return false;
    if(tileId == 101)
        return true;
    if(tileId == 102)
        return true;
    if(tileId == 103)
        return true;
    if(tileId == 104)
        return true;
    if(tileId == 105)
        return true;
    if(tileId == 106)
        return true;
    if(tileId == 107)
        return true;
    return false;
}

void MapManager::unloadMap()
{
    EntityManager::Instance().clearByType("Tile");
}

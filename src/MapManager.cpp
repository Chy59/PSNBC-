#include "MapManager.h"

int MapManager::m_gridSize;
Texture MapManager::m_texture;
MapManager MapManager::m_instance = MapManager();

MapManager& MapManager::getInstance()
{
    return m_instance;
}

MapManager::MapManager()
{
    m_gridSize = 32;
    m_texture = AssetsManager::getInstance().getTexture("images/tileset-platformer.png");
}

void MapManager::loadMap(const char* map_name)
{
    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse( AssetsManager::getInstance().getFile(map_name), root );

    if(!parsingSuccessful)
    {
        cout << "Failed to parse configuration" << endl << reader.getFormattedErrorMessages() << endl;
    }

    Json::Value layers = root["layers"];
    Json::Value tiles = layers[0]["data"];
    Json::Value tilesets = root["tilesets"];
    Json::Value properties = tilesets[0]["tileproperties"];

    int columns = layers[0].get("width", 0).asInt() - 1;
    int currentColumn = 0;
    int currentRow = 0;

    for(int index = 0, len = tiles.size(); index < len; ++index)
    {
        int line = tiles[index].asInt();
        if(line > 0)
        {
            --line;
            ostringstream ss;
            ss << line;
            string s_line = ss.str();
            float angle = 0;
            int base_y = 0;
            bool inverted = false;
            if(properties.isMember(s_line))
            {
                string attr;
                attr = properties[s_line].get("angle", 0).asString();
                angle = atof(attr.c_str()) * -1;

                attr = properties[s_line].get("y", 0).asString();
                base_y = atof(attr.c_str());

                attr = properties[s_line].get("inverted", 0).asString();
                istringstream(attr) >> inverted;
            }
            MapManager::getInstance().addTile(currentColumn, currentRow, line, angle, base_y, inverted);
        }
        if(currentColumn < columns)
            ++currentColumn;
        else
        {
            currentColumn = 0;
            ++currentRow;
        }
    }
}

void MapManager::addTile(float x, float y, int tileId, float angle, int base_y, bool side)
{
    Vector2f tile = MapManager::getInstance().getTileById(tileId);
    if(angle == 0 && base_y == 0)
        EntityManager::getInstance().addEntity(new Tile(x, y, tile.x, tile.y, m_texture, m_gridSize));
    else
        EntityManager::getInstance().addEntity(new Slope(x, y, tile.x, tile.y, m_texture, m_gridSize, angle, base_y, side));
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
    EntityManager::getInstance().clearByType("Tile");
}

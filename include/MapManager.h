#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>
#include <Tile.h>
#include <Math.h>
#include <fstream>

using namespace sf;

class MapManager
{
    public:
        static MapManager& Instance();
        static void loadMap(const char* mapName);
        static void addTile(float x, float y, int tileId);
        static Vector2f getTileById(int tileId);
        static void unloadMap();
    protected:
    private:
        MapManager();
        static MapManager m_instance;
        static Texture m_texture;
        static int m_gridSize;
};

#endif // MAPMANAGER_H

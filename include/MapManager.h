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
        MapManager(EntityManager* entityManager);
        void loadMap(const char* mapName);
        void addTile(float x, float y, int tileId);
        Vector2f getTileById(int tileId);
        void unloadMap();
    protected:
    private:
        Texture m_texture;
        int m_gridSize;
        EntityManager* m_entityManager;
};

#endif // MAPMANAGER_H

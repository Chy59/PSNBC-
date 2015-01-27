#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>
#include <Tile.h>
#include <Math.h>

using namespace sf;

class MapManager
{
    public:
        MapManager(EntityManager* entityManager);
        void generateMap();
        void addTile(float x, float y, int tileId);
        Vector2u getTileById(int tileId);
    protected:
    private:
        Texture m_texture;
        int m_gridSize;
        EntityManager* m_entityManager;
};

#endif // MAPMANAGER_H

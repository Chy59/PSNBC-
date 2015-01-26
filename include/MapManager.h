#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <SFML/Graphics.hpp>
#include <EntityManager.h>
#include <Tile.h>

using namespace sf;

class MapManager
{
    public:
        MapManager();
        void setEntityManager(EntityManager* em);
        void generateMap();
        void addTile(float x, float y, int tileX, int tileY);
    protected:
    private:
        Texture texture;
        int gridSize;
        EntityManager* entityManager;
};

#endif // MAPMANAGER_H

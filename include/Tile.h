#ifndef TILE_H
#define TILE_H

#include <Entity.h>

class Tile : public Entity
{
    public:
        Tile(float x, float y, int tileX, int tileY, Texture& texture, int gridSize);
        virtual void draw(RenderWindow& window);
        IntRect getTileById(int tileX, int tileY, int gridSize);
    protected:
    private:
        Sprite m_sprite;
};

#endif // TILE_H

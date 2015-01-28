#ifndef TILE_H
#define TILE_H

#include <Entity.h>

class Tile : public Entity
{
    public:
        Tile(float x, float y, int tileX, int tileY, Texture& texture, int gridSize);
        virtual void draw(RenderWindow& window);
        virtual FloatRect getBoundBox();
    protected:
        Sprite m_sprite;
    private:
};

#endif // TILE_H

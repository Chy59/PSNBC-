#ifndef SLOPE_H
#define SLOPE_H

#include <Tile.h>

class Slope : public Tile
{
    public:
        Slope(float x, float y, int tileX, int tileY, Texture& texture, int gridSize, Vector2f angle);
        Vector2f m_angle;
    protected:
    private:
};

#endif // SLOPE_H

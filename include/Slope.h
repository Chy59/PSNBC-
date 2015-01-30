#ifndef SLOPE_H
#define SLOPE_H

#include <Tile.h>

class Slope : public Tile
{
    public:
        Slope(float x, float y, int tileX, int tileY, Texture& texture, int gridSize, float angle, int base_y, bool inverted);
        float m_angle;
        int m_base_y;
        bool m_inverted;
    protected:
    private:
};

#endif // SLOPE_H

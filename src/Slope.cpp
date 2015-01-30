#include "Slope.h"

Slope::Slope(float x, float y, int tileX, int tileY, Texture& texture, int gridSize, float angle, int base_y, bool inverted) :
    Tile(x, y, tileX, tileY, texture, gridSize)
{
    m_angle = angle;
    m_base_y = base_y;
    m_inverted = inverted;
    m_type = "Slope";
}

#include "Slope.h"

Slope::Slope(float x, float y, int tileX, int tileY, Texture& texture, int gridSize, Vector2f angle) :
    Tile(x, y, tileX, tileY, texture, gridSize)
{
    m_angle = angle;
    m_type = "Slope";
}

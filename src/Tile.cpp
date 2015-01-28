#include "Tile.h"

Tile::Tile(float x, float y, int tileX, int tileY, Texture& texture, int gridSize)
{
    m_type = "Tile";
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(IntRect(tileX * gridSize, tileY * gridSize, gridSize, gridSize));
    m_sprite.move(x * gridSize, y * gridSize);
    m_hasCollisions = true;
}

void Tile::draw(RenderWindow& window)
{
    window.draw(m_sprite);
}

FloatRect Tile::getBoundBox()
{
    return m_sprite.getGlobalBounds();
}

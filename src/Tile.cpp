#include "Tile.h"

Tile::Tile(float x, float y, int tileX, int tileY, Texture& texture, int gridSize)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(this->getTileById(tileX, tileY, gridSize));
    m_sprite.move(x * gridSize, y * gridSize);
}

void Tile::draw(RenderWindow& window)
{
    window.draw(m_sprite);
}

IntRect Tile::getTileById(int tileX, int tileY, int gridSize)
{
    return IntRect(tileX * gridSize, tileY * gridSize, gridSize, gridSize);
}

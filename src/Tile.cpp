#include "Tile.h"

Tile::Tile(float x, float y, int tileX, int tileY, Texture& texture, int gridSize)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(this->getTileById(tileX, tileY, gridSize));
    sprite.move(x * gridSize, y * gridSize);
}

void Tile::draw(RenderWindow& window)
{
    window.draw(sprite);
}

IntRect Tile::getTileById(int tileX, int tileY, int gridSize)
{
    return IntRect(tileX * gridSize, tileY * gridSize, gridSize, gridSize);
}

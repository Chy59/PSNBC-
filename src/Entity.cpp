#include "Entity.h"

Entity::Entity()
{
    m_destroy = false;
    m_hasCollisions = false;
    m_type = "Entity";
}

void Entity::update(Time frameTime)
{
}

void Entity::draw(RenderWindow& window)
{
}

FloatRect Entity::getBoundBox()
{
    FloatRect boundBox;
    return boundBox;
}

Entity::~Entity()
{
}

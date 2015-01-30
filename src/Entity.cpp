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

float Entity::top()
{
    return this->getBoundBox().top;
}

float Entity::bottom()
{
    return this->getBoundBox().top + this->getBoundBox().height;
}

float Entity::right()
{
    return this->getBoundBox().left + this->getBoundBox().width;
}

float Entity::left()
{
    return this->getBoundBox().left;
}

Entity::~Entity()
{
}

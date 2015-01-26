#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::addEntity()
{
    MyShape* shape = new MyShape(0, 0);
    entities.push_back(shape);
}

void EntityManager::beforeDraw(Time frameTime)
{
    for(int i = 0, len = entities.size(); i < len; i++)
    {
        entities[i]->update(frameTime);
    }
}

void EntityManager::draw(RenderWindow& window)
{
    for(int i = 0, len = entities.size(); i < len; i++)
    {
        entities[i]->draw(window);
    }
}

void EntityManager::afterDraw()
{
    for(int i = 0, len = entities.size(); i < len; i++)
    {
        if(entities[i]->destroy)
        {
            delete entities[i];
            entities.erase(entities.begin() + i);
        }
    }
}

#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void EntityManager::beforeDraw(Time frameTime)
{
    for(int i = 0, len = m_entities.size(); i < len; i++)
    {
        m_entities[i]->update(frameTime);
    }
}

void EntityManager::draw(RenderWindow& window)
{
    for(int i = 0, len = m_entities.size(); i < len; i++)
    {
        m_entities[i]->draw(window);
    }
}

void EntityManager::afterDraw()
{
    for(int i = 0, len = m_entities.size(); i < len; i++)
    {
        if(m_entities[i]->m_destroy)
        {
            delete m_entities[i];
            m_entities.erase(m_entities.begin() + i);
        }
    }
}

vector<Entity*> EntityManager::getEntities()
{
    return m_entities;
}

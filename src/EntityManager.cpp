#include "EntityManager.h"

vector<Entity*> EntityManager::m_entities;
EntityManager EntityManager::m_instance = EntityManager();

EntityManager& EntityManager::getInstance()
{
    return m_instance;
}

EntityManager::EntityManager()
{
}

void EntityManager::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void EntityManager::beforeDraw(Time frameTime)
{
    for(int i = 0, len = m_entities.size(); i < len; ++i)
    {
        m_entities[i]->update(frameTime);
    }
}

void EntityManager::draw(RenderWindow& window)
{
    for(int i = 0, len = m_entities.size(); i < len; ++i)
    {
        m_entities[i]->draw(window);
    }
}

bool should_be_removed(Entity* entity)
{
   return entity->m_destroy;
}

void EntityManager::afterDraw()
{
    m_entities.erase( remove_if(m_entities.begin(), m_entities.end(), should_be_removed), m_entities.end() );
}

vector<Entity*> EntityManager::getEntities()
{
    return m_entities;
}

void EntityManager::clearByType(const char* type)
{
    for(int i = 0, len = m_entities.size(); i < len; ++i)
    {
        if(m_entities[i]->m_type == type)
        {
            m_entities[i]->m_destroy = true;
        }
    }
}

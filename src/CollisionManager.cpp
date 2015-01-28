#include "CollisionManager.h"

CollisionManager CollisionManager::m_instance = CollisionManager();

CollisionManager& CollisionManager::Instance()
{
    return m_instance;
}

CollisionManager::CollisionManager()
{
}

void CollisionManager::update(Player* player)
{
    vector<Entity*> entities = EntityManager::Instance().getEntities();
    for(int i = 0, len = entities.size(); i < len; ++i)
    {
        if(entities[i]->m_hasCollisions)
        {
            if(CollisionManager::Instance().collideAABB(entities[i], player))
            {
                player->collide(entities[i]);
            }
        }
    }
}

bool CollisionManager::collideAABB(Entity* e1, Entity* e2)
{
    return e1->getBoundBox().intersects(e2->getBoundBox());
}

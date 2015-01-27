#include "CollisionManager.h"

CollisionManager::CollisionManager(EntityManager* entityManager) :
    m_entityManager(entityManager)
{
}

void CollisionManager::update(Player* player)
{
    vector<Entity*> entities = m_entityManager->getEntities();
    for(int i = 0, len = entities.size(); i < len; i++)
    {
        if(entities[i]->m_hasCollisions)
        {
            if(this->collideAABB(entities[i], player))
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

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <EntityManager.h>
#include <Player.h>

class CollisionManager
{
    public:
        CollisionManager(EntityManager* entityManager);
        void update(Player* player);
        bool collideAABB(Entity* e1, Entity* e2);
    protected:
    private:
        EntityManager* m_entityManager;
};

#endif // COLLISIONMANAGER_H

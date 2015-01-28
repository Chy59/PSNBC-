#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <EntityManager.h>
#include <Player.h>

class CollisionManager
{
    public:
        static CollisionManager& Instance();
        static void update(Player* player);
        static bool collideAABB(Entity* e1, Entity* e2);
    protected:
    private:
        CollisionManager();
        static CollisionManager m_instance;
};

#endif // COLLISIONMANAGER_H

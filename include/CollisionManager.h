#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <EntityManager.h>

class CollisionManager
{
    public:
        static CollisionManager& getInstance();
        static bool collideAABB(FloatRect e1, FloatRect e2);
    protected:
    private:
        CollisionManager();
        static CollisionManager m_instance;
};

#endif // COLLISIONMANAGER_H

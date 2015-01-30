#include "CollisionManager.h"

CollisionManager CollisionManager::m_instance = CollisionManager();

CollisionManager& CollisionManager::getInstance()
{
    return m_instance;
}

CollisionManager::CollisionManager()
{
}

bool CollisionManager::collideAABB(FloatRect e1, FloatRect e2)
{
    return e1.intersects(e2);
}

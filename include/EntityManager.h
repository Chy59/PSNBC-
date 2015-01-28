#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <Entity.h>

class EntityManager
{
    public:
        static EntityManager& Instance();
        static void addEntity(Entity* entity);
        static void beforeDraw(Time frameTime);
        static void draw(RenderWindow& window);
        static void afterDraw();
        static vector<Entity*> getEntities();
        static void clearByType(const char* type);
    protected:
    private:
        EntityManager();
        static EntityManager m_instance;
        static vector<Entity*> m_entities;
};

#endif // ENTITYMANAGER_H

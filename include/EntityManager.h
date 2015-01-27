#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <Entity.h>

class EntityManager
{
    public:
        EntityManager();
        void addEntity(Entity* entity);
        void beforeDraw(Time frameTime);
        void draw(RenderWindow& window);
        void afterDraw();
        vector<Entity*> getEntities();
        void clearByType(const char* type);
    protected:
    private:
        vector<Entity*> m_entities;
};

#endif // ENTITYMANAGER_H

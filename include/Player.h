#ifndef PLAYER_H
#define PLAYER_H

#include <MapManager.h>
#include <CollisionManager.h>

class Player : public Entity
{
    public:
        Player();
        virtual void update(Time frameTime);
        virtual void draw(RenderWindow& window);
        virtual FloatRect getBoundBox();
        void collide(Entity* entity);
        void doCollisions();
    protected:
    private:
        Texture m_texture;
        Animation m_walkingAnimationRight;
        Animation* m_currentAnimation;
        AnimatedSprite m_animatedSprite;
        float m_gravity;
        float m_speed;
        int m_side;
        Vector2f m_oldPosition;
        float m_jump_velocity;
        float m_jump_max_velocity;
        bool m_jumping;
        float m_jump_deceleration;
        bool m_canJump;
};

#endif // PLAYER_H

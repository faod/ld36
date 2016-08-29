#pragma once

#include <objects/CollidableObject.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace faod
{
    class CollisionManager;
    class Projectile : public CollidableObject
    {
        public:
            Projectile(sf::Texture &texture, int startw, int starth, float weight, int textx, int texty, CollisionManager *manager);
            void launch(sf::Vector2f dir, float force);

            void collideWith(CollidableObject &other);

            //virtual Collision::Type getCollisionType() const;
        protected:
            bool launched_;

        private:        
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void updateCurrent(sf::Time delta);
        private:
            float weight_;
            sf::Texture     &texture_;
            sf::Sprite       sprite_;
    };

    class Pumpkin : public Projectile
    {
        public:
            Pumpkin(sf::Texture &texture, int startw, int starth, CollisionManager *manager);

            virtual Collision::Type getCollisionType() const;
    };

    class Rock : public Projectile
    {
        public:
            Rock(sf::Texture &texture, int startw, int starth, CollisionManager *manager);

            virtual Collision::Type getCollisionType() const;
    };

}

#pragma once

#include <utils/Animation.hpp>
#include <game/World.hpp>
#include <objects/CollidableObject.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace faod
{
    class CollisionManager;
    class Foe: public CollidableObject
    {

        public:
            Foe(World *world, sf::Texture &texture, int row, int spawn_x, int spawn_y, float orient, CollisionManager *manager);

            ConvexHull getFOV() const;
            void collideWith(CollidableObject &other);
            virtual Collision::Type getCollisionType() const;
        private:
            virtual void updateCurrent(sf::Time delta);
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void drawDebug(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            //Graphics
            sf::Texture             &texture_;
            sf::Sprite              *current_;
            Animation               walkAnimation_;
            Animation               shieldAnimation_;
            Animation               swordAnimation1_;
            Animation               swordAnimation2_;

            //Game logic
            World                   *world_; // to getCatapult()
            unsigned int            hp_;
            bool                    performing_; // Action doing
            bool                    blocking_;   // Cannot be stopped if true
            Animation               *perform_;   // What action

            static ConvexHull fov;
    };
}

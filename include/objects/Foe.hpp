#pragma once

#include <utils/Animation.hpp>
#include <objects/CollidableObject.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace faod
{
    class CollisionManager;
    class Foe: public CollidableObject
    {
        public:
            Foe(sf::Texture &texture, int row, int spawn_x, int spawn_y, CollisionManager *manager);


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
            unsigned int hp_;
    };
}

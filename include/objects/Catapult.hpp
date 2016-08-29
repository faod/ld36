#pragma once

#include <utils/Animation.hpp>
#include <resources/ResourceHolder.hpp>
#include <objects/CollidableObject.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>

namespace faod
{
    class Catapult : public CollidableObject
    {
        public:
            Catapult(sf::Texture &texture, ResourceHolder<sf::Font, std::string> *fonts,int startw = 400, int starth = 300);

            virtual unsigned int getCategory() const;

            //Called to request a movement in the [-100. : 100.] range
            void moveInput(sf::Vector2f movement, sf::Time delta);
            //Called to request a throw
            void throwProjectile(sf::Time delta);

            float getForceMin() const;
            float getForceMax() const;
            float getCurrentForce() const;

            void collideWith(CollidableObject &other);
            virtual Collision::Type getCollisionType() const;
        private:
            virtual void updateCurrent(sf::Time delta);
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void drawDebug(sf::RenderTarget& target,   sf::RenderStates states) const;
                    void updateMovementBoundaries();
                    void updateThrow(sf::Time delta);

        private:
            static const float forcemin_;
            static const float initialforcemax_;
            static const float initialmaxsteeringangle_;
            static const float initialmaxvelocity_;
        private:
            ResourceHolder<sf::Font, std::string> *fonts_;
            //Game logic
            unsigned int            hp_;
            unsigned int            ammo_;
            float                   forcemax_;
            //rad, counterclockwise
            float                   maxsteeringangle_;
            float                   maxvelocity_;

            //Graphics
            sf::Texture             &texture_;
            sf::Sprite              *current_;

            //Throwing projectile related vars
            Animation               animation_;
            bool                    throwing_;
            bool                    throwPressed_;
            float                   currentForce_;
    };
}

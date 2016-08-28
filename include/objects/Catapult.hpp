#pragma once

#include <resources/ResourceHolder.hpp>
#include <objects/CollidableObject.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>

namespace faod
{
    class Catapult : public CollidableObject
    {
        public:
            Catapult(sf::Texture &texture, ResourceHolder<sf::Font, std::string> *fonts,int startw = 400, int starth = 300);

            virtual unsigned int getCategory() const;

            //Called to request a movement in the [-100. : 100.] range
            void moveInput(sf::Vector2f movement, sf::Time delta);

        private:
            virtual void updateCurrent(sf::Time delta);
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void drawDebug(sf::RenderTarget& target,   sf::RenderStates states) const;
                    void updateMovementBoundaries();
        private:
            struct Sprite
            {
                sf::Sprite sprite;
                float      timetonext;
            };

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
            std::array<Sprite, 8>   sprites_;
            size_t                  currentframe_;
    };
}

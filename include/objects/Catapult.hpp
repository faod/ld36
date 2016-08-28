#pragma once

#include <objects/CollidableObject.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace faod
{
    class Catapult : public CollidableObject
    {
        public:
            Catapult(sf::Texture &texture, int startw = 400, int starth = 300);




        private:
            virtual void updateCurrent(sf::Time delta);
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            struct Sprite
            {
                sf::Sprite sprite;
                float      timetonext;
            };

        private:
            static const float forcemin_; 
            static const float initialforcemax_;

        private:
            
            //Game logic
            unsigned int            hp_;
            unsigned int            ammo_;
            float                   forcemax_;


            //Graphics
            sf::Texture             &texture_;
            std::array<Sprite, 8>   sprites_;
            size_t                  currentframe_;
    };
}

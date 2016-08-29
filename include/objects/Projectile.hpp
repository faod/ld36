#pragma once

#include <objects/CollidableObject.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace faod
{
    class Projectile : public CollidableObject
    {
        public:
            Projectile(sf::Texture &texture, int startw, int starth, float weight, int textx, int texty);
            void launch(sf::Vector2f dir, float force);

        private:
            float weight_;
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            //graphics
            sf::Texture     &texture_;
            sf::Sprite       sprite_;
    };

    class Pumpkin : public Projectile
    {
        public:
            Pumpkin(sf::Texture &texture, int startw, int starth);
    };

}

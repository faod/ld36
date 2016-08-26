#pragma once

#include <objects/SceneNode.hpp>

#include <SFML/System/Time.hpp>

namespace faod
{
    //Mov(ing)/(able) SceneNode
    class Object : public SceneNode
    {
        public:
           void             setVelocity(sf::Vector2f velocity);
           void             setVelocity(float vx, float vy);
           void             accelerate(sf::Vector2f velocity);
           void             accelerate(float vx, float vy);
           sf::Vector2f     getVelocity() const;

        private:
           virtual void     updateCurrent(sf::Time delta);

        private:
           sf::Vector2f    velocity_;
    };
}

#pragma once

#include <objects/SceneNode.hpp>

#include <SFML/System/Time.hpp>

namespace faod
{
    //Mov(ing)/(able) SceneNode
    class Object : public SceneNode
    {
        public:
           Object(const Object& o) = delete;
           Object(Object &&o)      = delete;
           Object& operator=(const Object& o) = delete;
           Object& operator=(Object&& o)      = delete;

            
           Object() = default;

           void             setVelocity(sf::Vector2f velocity);
           void             setVelocity(float vx, float vy);
           //set acceleration in pixel/s^2
           void             setAcceleration(sf::Vector2f acceleration);
           void             setAcceleration(float ax, float ay);

           //instantaneous acceleration
           void             accelerate(sf::Vector2f velocity);
           void             accelerate(float vx, float vy);
           
           sf::Vector2f     getVelocity() const;
           sf::Vector2f     getAcceleration() const;
        private:
           virtual void     updateCurrent(sf::Time delta);

        private:
           sf::Vector2f    velocity_;
           sf::Vector2f    acceleration_;
    };
}

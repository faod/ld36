#include <objects/Object.hpp>

#include <glm/glm.hpp>


namespace faod
{
    float Object::degToRad(float angle)
    {
        return -((angle / 180) * 3.141592654f);
    }
    float Object::radToDeg(float omega)
    {
        return -((omega / 3.141592654f) * 180);
    }
    void Object::setVelocity(sf::Vector2f velocity)
    {
        velocity_ = velocity;
    }

    void Object::setVelocity(float vx, float vy)
    {
        velocity_.x = vx;
        velocity_.y = vy;
    }

    sf::Vector2f Object::getVelocity() const
    {
        return velocity_;
    }

    void Object::accelerate(sf::Vector2f velocity)
    {
        acceleration_ += velocity;
    }

    void Object::accelerate(float vx, float vy)
    {
        velocity_.x += vx;
        velocity_.y += vy;
    }
    void Object::setAcceleration(sf::Vector2f acceleration)
    {
        acceleration_ = acceleration;
    }
    void Object::setAcceleration(float ax, float ay)
    {
        acceleration_.x = ax;
        acceleration_.y = ay;
    }

    sf::Vector2f Object::getAcceleration() const
    {
        return acceleration_;
    }

    void Object::updateCurrent(sf::Time delta)
    {
        //adding up the effect of acceleration
        velocity_ += (acceleration_ * delta.asSeconds());
               
        //axis relative to local reference
        if(getRotation() != 0)
        {
            float s, c;
            c = cos(-degToRad(getRotation()));
            s = sin(-degToRad(getRotation()));
            
            glm::mat2 rotm(c ,s ,-s, c);
            glm::vec2 dir(velocity_.x, velocity_.y);
            dir = rotm * dir;
            dir = delta.asSeconds() * dir;            
            move(sf::Vector2f(dir.x, dir.y));
        }
        else
        {
            move(velocity_ * delta.asSeconds());
        }
    }
}

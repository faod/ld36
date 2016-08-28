#include <objects/Object.hpp>


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
        //calling sf::transform::move()
        move(velocity_ * delta.asSeconds());
    }
}

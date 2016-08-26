#include <objects/Object.hpp>


namespace faod
{
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
        velocity_ += velocity;
    }

    void Object::accelerate(float vx, float vy)
    {
        velocity_.x += vx;
        velocity_.y += vy;
    }
    void Object::updateCurrent(sf::Time delta)
    {
        //calling sf::transform::move()
        move(velocity_ * delta.asSeconds());
    }
}

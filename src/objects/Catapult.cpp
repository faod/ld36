#include <objects/Catapult.hpp>
#include <objects/Projectile.hpp>
#include <game/Identifiers.hpp>
#include <objects/CollisionManager.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <sstream>
#include <iostream>
#include <iomanip>

namespace faod
{
    const float Catapult::forcemin_ = 1.;
    const float Catapult::initialforcemax_ = 2.;
    const float Catapult::initialmaxvelocity_  = 30.;

    Catapult::Catapult(sf::Texture &texture, ResourceHolder<sf::Font, std::string> *fonts, CollisionManager *manager, int startx, int starty)
        :CollidableObject(ConvexHull::boxHull(glm::vec2(60., 64.)), manager)
        ,fonts_(fonts)
        ,hp_(100)
        ,forcemax_(initialforcemax_)
        ,maxvelocity_(initialmaxvelocity_)
        ,texture_(texture)
        ,animation_(false)
        ,throwing_(false)
        ,throwPressed_(false)
        ,currentForce_(forcemin_)
        ,projectile_(nullptr)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture_);

        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(192, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(256, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(320, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(384, 0, 64, 64));
        animation_.addFrame(sprite, 60);

        sprite.setTextureRect(sf::IntRect(448, 0, 64, 64));
        animation_.addFrame(sprite, 400);

        // Reverse animation
        animation_.addFrame(*(animation_.getFrame(6)), 200);
        animation_.addFrame(*(animation_.getFrame(5)), 200);
        animation_.addFrame(*(animation_.getFrame(4)), 200);
        animation_.addFrame(*(animation_.getFrame(3)), 200);
        animation_.addFrame(*(animation_.getFrame(2)), 200);
        animation_.addFrame(*(animation_.getFrame(1)), 200);
        animation_.addFrame(*(animation_.getFrame(0)), 200);

        current_ = animation_.getFrame(0);

        setOrigin(33, 32);
        setPosition(startx, starty);
    }
    void Catapult::moveInput(sf::Vector2f movement, sf::Time delta)
    {
        (void) delta;
        if(movement.y < 0.)
        {
            setAcceleration(0. , -10.);
        }
        if(movement.y > 0.)
        {
            setAcceleration(0., 10.);
        }
        if(movement.x < 0.)
        {
            rotate(-1);
        }
        if(movement.x > 0.)
        {
            rotate(1);
        }
    }
    float Catapult::getForceMin() const
    {
        return forcemin_;
    }
    float Catapult::getForceMax() const
    {
        return forcemax_;
    }
    float Catapult::getCurrentForce() const
    {
        return currentForce_;
    }

    int Catapult::getHealth() const
    {
        return hp_;
    }

    void Catapult::endure(int dmg)
    {
        hp_ -= dmg;
        if (hp_ <= 0)
        {
            std::cout << "you ded -_-" << std::endl;
            // TODO Game Over
        }
    }

    void Catapult::updateCurrent(sf::Time delta)
    {
        updateMovementBoundaries();


        //Call CollidableObject::update
        //Collisions will be calculated and then object will be moved (or not if colliding)
        CollidableObject::updateCurrent(delta);
        manager_->collisionCheck(*this);        

        updateThrow(delta);


        setAcceleration(0., 0.);
    }
    void Catapult::updateThrow(sf::Time delta)
    {
        if(!throwing_ && !throwPressed_)
        {
            //If we are not currently throwing and throw key not pressed
            if(currentForce_ > forcemin_)
            {
                //if the current force is different of forcemin_
                //we are throwing
                throwing_ = true;
                currentForce_ = forcemin_;
                animation_.reset();
            }
        }
        if(throwing_)
        {
            animation_.update(delta.asMilliseconds());
            current_ = animation_.getCurrentSprite();
            if(!current_)
            {
                current_ = animation_.getFrame(0);
                throwing_ = false;
            }
        }
        //we reset throwPressed
        throwPressed_ = false;
    }

    void Catapult::updateMovementBoundaries()
    {
        if(getVelocity().y > maxvelocity_ && getAcceleration().y > 0)
        {
            setAcceleration(0., 0.);
            setVelocity(0., maxvelocity_);
        }
        if(getVelocity().y < -maxvelocity_ && getAcceleration().y < 0)
        {
            setAcceleration(0., 0.);
            setVelocity(0., -maxvelocity_);
        }

    }
    void Catapult::throwProjectile(sf::Time delta)
    {
        //time for full throw in sec
        const float timeToFull = 1.2;
        const float increment  = (((forcemax_ - forcemin_) / timeToFull) * delta.asSeconds());

        if(throwing_) return;

        throwPressed_ = true;
        if(currentForce_ + increment < forcemax_)
        {
            currentForce_ += increment;
        }
        else
        {
            currentForce_ = forcemax_;
            throwing_ = true;
        }
    }

    void Catapult::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(*current_, states);

    }
    void Catapult::collideWith(CollidableObject &other)
    {
        //check for type
        if(other.getCollisionType() == Collision::Type::Bonus)
        {
            try
            {
                //is it a projectile?
                //
                Projectile &p = dynamic_cast<Projectile&>(other);    
                
                //can we pick it up?
                if(projectile_)
                    return;

                auto temp = parent_->detachChild(p);
                attachChild(temp);
                projectile_ = static_cast<Projectile*>(temp.get());
                projectile_->pickedUp(*this);

            } catch(std::bad_cast)
            {
                //Not a projectile
            }
        }
    }

    void Catapult::drawDebug(sf::RenderTarget &target, sf::RenderStates states) const
    {
        CollidableObject::drawDebug(target, states);
        static sf::Text speed("speed", fonts_->get("pixel"), 12);

        speed.setFillColor(sf::Color(0,0,255));


        std::ostringstream oss;
        oss << "speed: " << std::setprecision(3) << getVelocity().x << " ; " << getVelocity().y;
        speed.setString(oss.str());
        oss.clear();
        oss.str(std::string(""));

        target.draw(speed);
    }
    unsigned int Catapult::getCategory() const
    {
        return Category::Catapult;
    }
    Collision::Type Catapult::getCollisionType() const
    {
        return Collision::Type::Catapult;
    }
}

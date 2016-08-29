#include <objects/Catapult.hpp>
#include <game/Identifiers.hpp>

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

    Catapult::Catapult(sf::Texture &texture, ResourceHolder<sf::Font, std::string> *fonts, int startx, int starty)
        :CollidableObject(ConvexHull(0)) //FIXME
        ,fonts_(fonts)
        ,hp_(100)
        ,ammo_(3)
        ,forcemax_(initialforcemax_)
        ,maxvelocity_(initialmaxvelocity_)
        ,texture_(texture)
        ,currentframe_(0)
        ,throwing_(false)
        ,throwPressed_(false)
        ,currentForce_(forcemin_)
    {
        sprites_[0].sprite.setTexture(texture_);
        sprites_[0].sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        sprites_[0].timetonext = 0.1;

        sprites_[1].sprite.setTexture(texture_);
        sprites_[1].sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
        sprites_[1].timetonext = 0.1;

        sprites_[2].sprite.setTexture(texture_);
        sprites_[2].sprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
        sprites_[2].timetonext = 0.1;

        sprites_[3].sprite.setTexture(texture_);
        sprites_[3].sprite.setTextureRect(sf::IntRect(192, 0, 64, 64));
        sprites_[3].timetonext = 0.1;

        sprites_[4].sprite.setTexture(texture_);
        sprites_[4].sprite.setTextureRect(sf::IntRect(256, 0, 64, 64));
        sprites_[4].timetonext = 0.1;

        sprites_[5].sprite.setTexture(texture_);
        sprites_[5].sprite.setTextureRect(sf::IntRect(320, 0, 64, 64));
        sprites_[5].timetonext = 0.1;

        sprites_[6].sprite.setTexture(texture_);
        sprites_[6].sprite.setTextureRect(sf::IntRect(384, 0, 64, 64));
        sprites_[6].timetonext = 0.1;

        sprites_[7].sprite.setTexture(texture_);
        sprites_[7].sprite.setTextureRect(sf::IntRect(448, 0, 64, 64));
        sprites_[7].timetonext = 0.1;

        setPosition(startx, starty);
        setOrigin(33, 32);
    }
    void Catapult::moveInput(sf::Vector2f movement, sf::Time delta)
    {
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

    void Catapult::updateCurrent(sf::Time delta)
    {
        updateMovementBoundaries();        


        //Call CollidableObject::update
        //Collisions will be calculated and then object will be moved (or not if colliding
        CollidableObject::updateCurrent(delta);

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
                elapsedTime_.restart();
            }
        }
        if(throwing_)
        {
            //we can animate the catapult
            if(elapsedTime_.getElapsedTime().asSeconds() > sprites_[currentframe_].timetonext)
            {
                if(currentframe_ < 7 && currentForce_ > forcemin_)
                {
                    currentframe_++;
                    elapsedTime_.restart();
                }
                if(currentframe_ == 7)
                {
                    currentframe_--;
                    currentForce_ = forcemin_;
                    elapsedTime_.restart();
                    //throw projectile
                }
                if(currentframe_ > 0 && currentForce_ <= forcemin_)
                {
                    currentframe_--;
                    elapsedTime_.restart();
                }
                if(currentframe_ == 0 && currentForce_ <= forcemin_)
                {
                    throwing_ = false;               
                }
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
        target.draw(sprites_[currentframe_].sprite, states);

    }
    void Catapult::drawDebug(sf::RenderTarget &target, sf::RenderStates states) const
    {
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
}

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

    void Catapult::updateCurrent(sf::Time delta)
    {
        updateMovementBoundaries();        
        
        //Update rotation to face velocity vector
        {

            glm::vec2 currvelocity(getVelocity().x, getVelocity().y);
            if(0)
            {
                currvelocity = glm::normalize(currvelocity);
                float omega = glm::acos(glm::dot(currvelocity, glm::vec2(0., -1.)));
            
                glm::vec3 dummy = glm::cross(glm::vec3(currvelocity, 0.), glm::vec3(0., -1., 0.));
                omega = dummy.z >= 0 ? omega : -omega;
                setRotation(radToDeg(omega));
            }

        }

        //Call CollidableObject::update
        //Collisions will be calculated and then object will be moved (or not if colliding
        CollidableObject::updateCurrent(delta);


/*
        //Cancel movement
        glm::vec2 currvelocity = glm::vec2(getVelocity().x, getVelocity().y);
        glm::vec2 curraccel = glm::vec2(getAcceleration().x, getAcceleration().y) ;
        if(glm::length(currvelocity) > 5.)
        {
            setAcceleration(sf::Vector2f(curraccel.x, curraccel.y));
        }
        else
        {
            setVelocity(0.,0.);
        }
        */

        setAcceleration(0., 0.);
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

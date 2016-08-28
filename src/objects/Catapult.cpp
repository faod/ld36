#include <objects/Catapult.hpp>
#include <game/Identifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


namespace faod
{
    const float Catapult::forcemin_ = 1.;
    const float Catapult::initialforcemax_ = 2.;
    const float Catapult::initialmaxsteeringangle_ = PI/6;

    Catapult::Catapult(sf::Texture &texture, int startx, int starty)
        :CollidableObject(ConvexHull(0)) //FIXME
        ,hp_(100)
        ,ammo_(3)
        ,forcemax_(initialforcemax_)
        ,maxsteeringangle_(initialmaxsteeringangle_)
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
    }
    
    void Catapult::moveInput(sf::Vector2f movement, sf::Time delta)
    {
        setVelocity(-20., 0.);
    }

    void Catapult::updateCurrent(sf::Time delta)
    {
        //Call CollidableObject::update
        //Collisions will be calculated and then object will be moved (or not if colliding
        CollidableObject::updateCurrent(delta);
    }

    void Catapult::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprites_[currentframe_].sprite, states);
    }

    unsigned int Catapult::getCategory() const
    {
        return Category::Catapult;
    }
}

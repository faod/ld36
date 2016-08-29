#include <objects/Projectile.hpp>
#include <objects/Catapult.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
namespace faod
{
    Projectile::Projectile(sf::Texture &texture, int startw, int starth, float weight, int textx, int texty)
        :CollidableObject(ConvexHull::boxHull(glm::vec2(16., 16.)))
        ,weight_(weight)
        ,texture_(texture)
        ,launched_(false)
    {
        sprite_.setTexture(texture_);
        sprite_.setTextureRect(sf::IntRect(textx,texty,16,16));
        setOrigin(6, 6);
        setPosition(startw, starth);
    }

    void Projectile::launch(sf::Vector2f dir, float force)
    {
    }
    
    void Projectile::updateCurrent(sf::Time delta)
    {

    }
    void Projectile::collideWith(CollidableObject &other)
    {

    }

    void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite_, states);
    }

    Pumpkin::Pumpkin(sf::Texture &texture, int startw, int starth)
        :Projectile(texture, startw, starth, 10., 0, 240)
    {
    }
    Collision::Type Pumpkin::getCollisionType() const
    {
        SceneNode *dummy = nullptr;


        dummy = dynamic_cast<Catapult*>(parent_);
        if(dummy == nullptr && !launched_)
            return Collision::Type::Bonus;
        if(dummy == nullptr && launched_)
            return Collision::Type::Projectile; 
        
        return Collision::Type::None;
    }

    Rock::Rock(sf::Texture &texture, int startw, int starth)
        :Projectile(texture, startw, starth, 50., 64, 240)
    {
    }
    Collision::Type Rock::getCollisionType() const
    {
        SceneNode *dummy = nullptr;

        dummy = dynamic_cast<Catapult*>(parent_);
        if(dummy == nullptr && !launched_)
            return Collision::Type::Bonus;
        if(dummy == nullptr && launched_)
            return Collision::Type::Projectile; 
        
        return Collision::Type::None;
    }

}

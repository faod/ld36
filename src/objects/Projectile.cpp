#include <objects/Projectile.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
namespace faod
{
    Projectile::Projectile(sf::Texture &texture, int startw, int starth, float weight, int textx, int texty)
        :CollidableObject(ConvexHull(0)) //FIXME
        ,weight_(weight)
        ,texture_(texture)
    {
        sprite_.setTexture(texture_);
        sprite_.setTextureRect(sf::IntRect(textx,texty,16,16));
        setOrigin(6, 6);
        setPosition(startw, starth);
    }

    void Projectile::launch(sf::Vector2f dir, float force)
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

}

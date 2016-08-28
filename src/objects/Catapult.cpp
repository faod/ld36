#include <objects/Catapult.hpp>

namespace faod
{
    const float Catapult::forcemin_ = 1.;
    const float Catapult::initialforcemax_ = 2.;

    Catapult::Catapult(sf::Texture &texture)
        :CollidableObject(ConvexHull(0)) //FIXME
        ,hp_(100)
        ,ammo_(3)
        ,forcemax_(initialforcemax_)
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

    }


}

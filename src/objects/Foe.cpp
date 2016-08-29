#include <objects/Foe.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace faod
{
    ConvexHull Foe::fov = ConvexHull::triHull(4*32., 5*32., PI);

    Foe::Foe(sf::Texture &texture, int row, int spawn_x, int spawn_y, float orient, CollisionManager *manager):
        CollidableObject(ConvexHull::boxHull(glm::vec2(32., 24.)), manager),
        texture_(texture),
        walkAnimation_(true),
        shieldAnimation_(false),
        swordAnimation1_(false),
        swordAnimation2_(false),
        hp_(100)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture_);

        for (int it=0; it<8; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, 32, 48));
            walkAnimation_.addFrame(sprite, 120);
        }
        for (int it=9; it<12; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, 32, 48));
            shieldAnimation_.addFrame(sprite, 120);
        }
        for (int it=12; it<15; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, 32, 48));
            swordAnimation1_.addFrame(sprite, 100);
        }
        for (int it=15; it<21; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, 32, 48));
            swordAnimation2_.addFrame(sprite, 80);
        }

        current_ = walkAnimation_.getFrame(0);

        setOrigin(16, 32);
        setPosition(spawn_x, spawn_y);
        setRotation(orient);
    }

    ConvexHull Foe::getFOV() const
    {
        ConvexHull c = fov;
        c.rotate(getRotation()*PI/180.);
        c.translate(glm::vec2(getPosition().x, getPosition().y));
        return c;
    }

    void Foe::updateCurrent(sf::Time delta)
    {
        (void) delta;
    }

    void Foe::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*current_, states);
    }

    void Foe::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
    {
        CollidableObject::drawDebug(target, states);
        getFOV().draw(target, states);
    }
    void Foe::collideWith(CollidableObject &other)
    {
    }
    Collision::Type Foe::getCollisionType() const
    {
        return Collision::Type::Foe;
    }

}

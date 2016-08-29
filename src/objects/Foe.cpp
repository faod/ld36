#include <objects/Foe.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace faod
{

    Foe::Foe(sf::Texture &texture, int row, int spawn_x, int spawn_y, CollisionManager *manager):
        CollidableObject(ConvexHull::boxHull(glm::vec2(32., 24.)), manager),
        texture_(texture),
        walkAnimation_(false),
        shieldAnimation_(false),
        swordAnimation1_(false),
        swordAnimation2_(false),
        hp_(100)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture_);

        for (int it=0; it<8; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, it*32+32, row*48+48));
            walkAnimation_.addFrame(sprite, 100);
        }
        for (int it=9; it<12; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, it*32+32, row*48+48));
            shieldAnimation_.addFrame(sprite, 100);
        }
        for (int it=12; it<15; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, it*32+32, row*48+48));
            swordAnimation1_.addFrame(sprite, 100);
        }
        for (int it=15; it<21; it++)
        {
            sprite.setTextureRect(sf::IntRect(it*32, row*48, it*32+32, row*48+48));
            swordAnimation2_.addFrame(sprite, 100);
        }

        current_ = walkAnimation_.getFrame(0);

        setOrigin(16, 32);
        setPosition(spawn_x, spawn_y);
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
    }
    void Foe::collideWith(CollidableObject &other)
    {
    }
    Collision::Type Foe::getCollisionType() const
    {
        return Collision::Type::Foe;
    }

}

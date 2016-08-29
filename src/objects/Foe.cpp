#include <objects/Foe.hpp>
#include <objects/Catapult.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <glm/glm.hpp>

namespace faod
{
    ConvexHull Foe::fov = ConvexHull::triHull(4*32., 5*32., PI);

    Foe::Foe(World *world, sf::Texture &texture, int row, int spawn_x, int spawn_y, float orient, CollisionManager *manager):
        CollidableObject(ConvexHull::boxHull(glm::vec2(32., 24.)), manager),
        texture_(texture),
        walkAnimation_(true),
        shieldAnimation_(false),
        swordAnimation1_(false),
        swordAnimation2_(false),
        world_(world),
        hp_(100),
        performing_(false),
        blocking_(false),
        perform_(nullptr)
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
        if (performing_ && perform_)
        {
            perform_->update(delta.asMilliseconds());
            current_ = perform_->getCurrentSprite();
            if (!current_)
            {
                current_    = walkAnimation_.getFrame(0);
                performing_ = false;
                blocking_   = false;
            }
        }
        if (!blocking_)
        {
            Catapult *cata = world_->getCatapult();
            ConvexHull cataBB = cata->getConvexHull();
            if (getFOV().intersects(cataBB) || cataBB.intersects(getFOV()))
            {
                glm::vec2 pos = glm::vec2(getPosition().x, getPosition().y);
                glm::vec2 dta = glm::vec2(cata->getPosition().x, cata->getPosition().y) - pos;
                glm::vec2 dir = glm::normalize(dta);

                if (glm::length(dta) < 48)
                {
                    // ATTACK
                    performing_ = true;
                    blocking_   = true;
                    perform_    = &swordAnimation2_;
                    swordAnimation2_.reset();
                }
                else
                {
                    // CHASE
                    pos += .35f * dir;
                    setPosition(pos.x, pos.y);

                    float orient = glm::acos(glm::dot(glm::vec2(0., 1.), dir)) * 180/PI;
                    orient *= -m_sign(dir.x);
                    setRotation(180+orient);

                    performing_ = true;
                    perform_    = &walkAnimation_;
                    walkAnimation_.reset();
                }
            }
            else
            {
                current_    = walkAnimation_.getFrame(0);
                performing_ = false;
                blocking_   = false;
            }
        }
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
        (void) other;
    }
    Collision::Type Foe::getCollisionType() const
    {
        return Collision::Type::Foe;
    }

}

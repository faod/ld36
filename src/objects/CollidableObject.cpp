#include <objects/CollidableObject.hpp>

namespace faod
{
    CollidableObject::CollidableObject(const ConvexHull& convexHull, CollisionManager *manager) : Object(), convexHull_(convexHull), manager_(manager)
    {
    }

    void    CollidableObject::updateCurrent(sf::Time delta)
    {
        (void) delta;
        //FIXME
        //
        //Check if movement will produce collision
        //if not call parent::updateCurrent(delta)
        Object::updateCurrent(delta);
    }

    void CollidableObject::drawDebug(sf::RenderTarget &target, sf::RenderStates states) const
    {
        convexHull_.draw(target, states);
    }

    bool CollidableObject::isColliding(const CollidableObject& other) const
    {
        const ConvexHull c1 = getConvexHull();
        const ConvexHull c2 = other.getConvexHull();

        return (c1.intersects(c2) || c2.intersects(c1));

    }

    ConvexHull CollidableObject::getConvexHull() const
    {
        ConvexHull c = convexHull_;
        c.rotate(((getRotation() / 360) * 2 * PI));
        c.translate(glm::vec2(getPosition().x, getPosition().y));
        return c;
    }

    glm::vec4 CollidableObject::getBoundingBox() const
    {
        return getConvexHull().getBoundingBox();
    }
    Collision::Type CollidableObject::getCollisionType() const
    {
        return Collision::Type::None;    
    }
}

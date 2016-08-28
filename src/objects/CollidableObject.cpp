#include <objects/CollidableObject.hpp>

namespace faod
{
    CollidableObject::CollidableObject(const ConvexHull& convexHull) : Object(), convexHull_(convexHull)
    {
    }

    void    CollidableObject::updateCurrent(sf::Time delta)
    {
        (void) delta;
        //FIXME
        //
        //Check if movement will produce collision
        //if not call parent::updateCurrent(delta)
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
        c.translate(glm::vec2(getPosition().x, getPosition().y));
        c.rotate(-((getRotation() / 360) * 2 * PI));
        return c;
    }

    glm::vec4 CollidableObject::getBoundingBox() const
    {
        return getConvexHull().getBoundingBox();
    }
}

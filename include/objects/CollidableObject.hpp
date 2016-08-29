#pragma once

#include <objects/Object.hpp>
#include <objects/ConvexHull.hpp>

namespace faod
{
    class CollidableObject : public Object
    {
        public:
            CollidableObject(const CollidableObject &o) = delete;
            CollidableObject(CollidableObject &&o)      = delete;
            CollidableObject& operator=(const CollidableObject &o) = delete;
            CollidableObject& operator=(CollidableObject &&o) = delete;


            explicit CollidableObject(const ConvexHull &convexHull);

            //true if the objects are currently colliding
            bool isColliding(const CollidableObject& other) const;

            //returns the convexHull for this object with proper translation rotation and scaling
            ConvexHull getConvexHull() const;

            //returns the axis aligned bounding box for this object (x, y, w, h)
            glm::vec4 getBoundingBox() const;

        protected:
            virtual void    updateCurrent(sf::Time delta);
            virtual void    drawDebug(sf::RenderTarget &target, sf::RenderStates states) const;
        private:
            ConvexHull convexHull_;

    };
}

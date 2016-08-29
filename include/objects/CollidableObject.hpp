#pragma once

#include <objects/Object.hpp>
#include <objects/ConvexHull.hpp>

#include <game/Identifiers.hpp>


namespace faod
{
    class CollisionManager;
    class CollidableObject : public Object
    {
        public:
            CollidableObject(const CollidableObject &o) = delete;
            CollidableObject(CollidableObject &&o)      = delete;
            CollidableObject& operator=(const CollidableObject &o) = delete;
            CollidableObject& operator=(CollidableObject &&o) = delete;


            CollidableObject(const ConvexHull &convexHull, CollisionManager *manager);

            //true if the objects are currently colliding
            bool isColliding(const CollidableObject& other) const;

            //returns the convexHull for this object with proper translation rotation and scaling
            ConvexHull getConvexHull() const;

            //returns the axis aligned bounding box for this object (x, y, w, h)
            glm::vec4 getBoundingBox() const;
            
            virtual Collision::Type getCollisionType() const;
        protected:
            virtual void    updateCurrent(sf::Time delta);
            virtual void    drawDebug(sf::RenderTarget &target, sf::RenderStates states) const;

            CollisionManager *manager_;
        private:
            ConvexHull convexHull_;

    };
}

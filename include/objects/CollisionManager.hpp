#pragma once

#include <game/Identifiers.hpp>
#include <objects/CollidableObject.hpp>

#include <map>

namespace faod
{
    class CollisionManager
    {
        public:
            CollisionManager();
            void    collisionCheck(CollidableObject& object);
            void    addCollidable(std::weak_ptr<CollidableObject> ptr);

        private:
            struct Collision
            {
                int mask;
                std::function<void(CollidableObject*, CollidableObject&)> action;
            };

            std::vector<std::weak_ptr<CollidableObject>> collidables_;
            std::map<faod::Collision::Type, Collision> collisions_;
    };

}

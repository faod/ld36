#include <objects/CollisionManager.hpp>

namespace faod
{
    CollisionManager::CollisionManager()
    {
        //add collisions to the map
    }
    void CollisionManager::collisionCheck(CollidableObject& object)
    {
        int mask = collisions_[object.getCollisionType()].mask;

        for(auto it = collidables_.begin(); it != collidables_.end(); ++it)
        {
            if(it->expired()) //if no more pointer on it pass it 
                continue;

            std::shared_ptr<CollidableObject> ptr = it->lock();
            if(ptr.get() == &object)
            {
                continue;
            }
            if(ptr->getCollisionType() & mask)
            {
                //able to collide
                if(object.isColliding(*ptr))
                {
                    collisions_[object.getCollisionType()].action(&object, *ptr);
                }
            }
        }
    }
    void CollisionManager::addCollidable(std::weak_ptr<CollidableObject> ptr)
    {
        collidables_.push_back(ptr);
    }
}

#include <objects/CollisionManager.hpp>

#include <objects/Catapult.hpp>
#include <objects/Projectile.hpp>
#include <objects/Foe.hpp>

namespace faod
{
    CollisionManager::CollisionManager()
    {
        //add collisions to the map
        //catapult collision
        Collision c;
        c.mask = faod::Collision::Type::Bonus | faod::Collision::Type::Destroyable | faod::Collision::Type::Solid | faod::Collision::Type::Foe;
        c.action = derivedCollision<Catapult>
            (std::bind(&Catapult::collideWith, std::placeholders::_1, std::placeholders::_2));
        collisions_[faod::Collision::Type::Catapult] = c;

        //projectile collision
        //c.mask = faod::Collision::Type::Foe | faod::Collision::Type::Solid | faod::Collision::Type::Destroyable;
        //c.action = derivedCollision<Projectile>
          //  (std::bind(&Projectile::collideWith, std::placeholders::_1, std::placeholders::_2));
        //collisions_[faod::Collision::Type::Projectile] = c;

        //foe collision
        c.mask = faod::Collision::Type::Catapult | faod::Collision::Type::Foe | faod::Collision::Type::Poison | faod::Collision::Type::Destroyable | faod::Collision::Type::Solid;
        c.action = derivedCollision<Foe>
            (std::bind(&Foe::collideWith, std::placeholders::_1, std::placeholders::_2));
        
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
            if(ptr->getCollisionType() != faod::Collision::Type::None && ptr->getCollisionType() & mask)
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

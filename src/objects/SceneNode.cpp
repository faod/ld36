#include <objects/SceneNode.hpp>


#include <algorithm>
#include <cassert>


namespace faod
{
    SceneNode::SceneNode() : children_(), parent_(nullptr)
    {        
    }

    void SceneNode::attachChild(Smart_ptr child)
    {
        child->parent_ = this;
        children_.push_back(std::move(child));
    }

    SceneNode::Smart_ptr SceneNode::detachChild(const SceneNode& node)
    {
        //look in the collection of children for the node matching the parameter
        auto found = std::find_if(children_.begin(), children_.end(), 
                [&] (Smart_ptr& p) { return p.get() == &node; });
        //Node expected to be child of this
        assert(found != children_.end());

        //move the child to a temporary smartptr
        Smart_ptr result = std::move(*found);
        result->parent_  = nullptr;

        //child to erase has been moved, it wont call its destructor
        children_.erase(found);

        //returning a smart_ptr holding the childNode
        return result;
    }

    void SceneNode::update(sf::Time delta)
    {
        updateCurrent(delta);
        updateChildren(delta);
    }

    sf::Vector2f SceneNode::getWorldPosition() const
    {   
        return getWorldTransform() * sf::Vector2f();
    }

    sf::Transform SceneNode::getWorldTransform() const
    {
        sf::Transform transform = sf::Transform::Identity;

        for(const SceneNode* node = this; node != nullptr; node = node->parent_)
        {
            transform = node->getTransform() * transform;   
        }

        return transform;
    }

    /*
     * Private functions
     */
    
    void SceneNode::updateCurrent(sf::Time delta)
    {
        //default implementation is void
        (void) delta;
    }

    void SceneNode::updateChildren(sf::Time delta)
    {
        for(Smart_ptr& child : children_)
        {
            child->update(delta);
        }
    }

}

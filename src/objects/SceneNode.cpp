#include <objects/SceneNode.hpp>

#include <game/Identifiers.hpp>

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
        children_.push_back(child);
    }

    SceneNode::Smart_ptr SceneNode::detachChild(const SceneNode& node)
    {
        //look in the collection of children for the node matching the parameter
        auto found = std::find_if(children_.begin(), children_.end(),
                [&] (Smart_ptr& p) { return p && p.get() == &node; });
        //Node expected to be child of this
        assert(found != children_.end());

        //move the child to a temporary smartptr
        Smart_ptr result(*found);
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

    void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //Apply transform of current node
        states.transform *= getTransform();

        //Draw node and then children with updated transform
        drawCurrent(target, states);
#ifndef NDEBUG
        drawDebug(target, states);
#endif
        drawChildren(target, states);
    }

    void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
    {
        (void) target, (void) states;
        //Default does nothing
    }
    void SceneNode::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
    {
        (void) target, (void) states;
    }
    void SceneNode::onCommand(const Command& command, sf::Time delta)
    {
        //Command current node if valid category
        if(command.category_ & getCategory())
        {
            command.action_(this, delta);
        }

        //Then command children
        for(Smart_ptr& child : children_)
        {
            child->onCommand(command, delta);
        }
    }

    unsigned int SceneNode::getCategory() const
    {
        //Default return as a Scene Category
        //Overload in specific nodes for proper category
        return Category::Scene;
    }

    void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(const Smart_ptr& child : children_)
        {
            child->draw(target, states);
        }
    }

}

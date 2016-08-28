#pragma once

#include <game/Command.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <memory>

namespace faod
{
    //Node representing a drawable element, be it a gameplay object or an HUD element
    //sf::Drawable part for the draw function
    //sf::Transformable for the position, rotation and scale information
    class SceneNode : public sf::Transformable, public sf::Drawable
    {
        public:
            typedef std::unique_ptr<SceneNode> Smart_ptr;

        public:


            //non copyable non movable
            SceneNode(const SceneNode& g) = delete;
            SceneNode& operator=(const SceneNode& g) = delete;
            SceneNode& operator=(const SceneNode&& g) = delete;
            SceneNode(SceneNode&& g) = delete;

            //default empty node
            SceneNode();
            virtual ~SceneNode() = default;

            //attach a child node to the current node
            void        attachChild(Smart_ptr child);

            //detach a child node of the current node, returns the smart_ptr handling the node
            Smart_ptr   detachChild(const SceneNode& node);

            //Called everytime the physics needs to be updated on the node
            void update(sf::Time delta);

            //get position and transform relative to world
            sf::Vector2f    getWorldPosition() const;
            sf::Transform   getWorldTransform() const;

            void                    onCommand(const Command& command, sf::Time delta);
            virtual unsigned int    getCategory() const;

        private:
            //Physics update functions
            virtual void    updateCurrent(sf::Time delta);
            void            updateChildren(sf::Time delta);

            //Draw functions
            virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
            void            drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


        private:
            std::vector<Smart_ptr>      children_;
            SceneNode*                  parent_;
    };
}

#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

#include <objects/SceneNode.hpp>
#include <game/CommandQueue.hpp>

//forward declaration
namespace sf
{
    class RenderWindow;
}

namespace faod
{
    class World
    {
        public:
            //Non copyable non movable
            World(const World& w) = delete;
            World& operator=(const World& w) = delete;
            World& operator=(const World&& w) = delete;
            World(World&& w) = delete;
        public:

            explicit World(sf::RenderWindow& window);
            
            //update and draw functions
            void update(sf::Time delta);
            void draw();

            CommandQueue&   getCommandQueue();

        private:
            void loadTextures();
            void buildScene();

        private:
            sf::RenderWindow&   window_;
            sf::View            view_;

            SceneNode           sceneGraph_;
            CommandQueue        commandQueue_;
        
    };
}

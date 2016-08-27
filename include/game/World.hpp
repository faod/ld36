#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

#include <STP/TMXLoader.hpp>

#include <objects/SceneNode.hpp>
#include <game/CommandQueue.hpp>
#include <resources/ResourceHolder.hpp>
#include <states/State.hpp>
#include <states/GameState.hpp>

//forward declaration
namespace sf
{
    class RenderWindow;
}

namespace faod
{
    class GameState;
    class World
    {
        public:
            //Non copyable non movable
            World(const World& w) = delete;
            World& operator=(const World& w) = delete;
            World& operator=(const World&& w) = delete;
            World(World&& w) = delete;
        public:

            World(sf::RenderWindow& window, GameState &state, State::Context context, std::string mapname);

            //update and draw functions
            void update(sf::Time delta);
            void draw();

            CommandQueue&   getCommandQueue();

        private:
            void loadTextures();
            void buildScene();
            void loadMap();

        private:
            sf::RenderWindow&   window_;
            sf::View            view_;

            //World/level specific textures
            ResourceHolder<sf::Texture, size_t> textures_;

            SceneNode           sceneGraph_;
            CommandQueue        commandQueue_;


            GameState *owningstate_;
            State::Context context_;

            //Reference to the current map
            std::string   mapname_;
            tmx::TileMap *map_;
            ResourceHolder<tmx::TileMap, std::string> *mapList_;
    };
}

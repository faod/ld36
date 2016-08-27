#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>

#include <resources/StpHolder.hpp>

#include <states/StateStack.hpp>
#include <game/PlayerController.hpp>
#include <resources/ResourceHolder.hpp>

namespace faod
{

    class Game
    {
        public:
            Game(const std::string& title, unsigned int width, unsigned int height);

            Game(const Game& g) = delete;
            Game& operator=(const Game& g) = delete;
            Game& operator=(const Game&& g) = delete;
            Game(Game&& g) = delete;

            void run();

        private:
            static const sf::Time TimePerFrame;

        private:
            void processInput();
            void update(sf::Time delta);
            void render();

            void loadFonts();
            void registerStates();
        private:

            sf::RenderWindow    window_;

            PlayerController    playerController_;

            //global textures manager
            ResourceHolder<sf::Texture, size_t> textures_;
            //global font manager
            ResourceHolder<sf::Font   , std::string> fonts_;

            //Map manager
            ResourceHolder<tmx::TileMap, std::string> maps_;

            StateStack          stateStack_;
    };

}

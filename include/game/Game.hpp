#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <states/StateStack.hpp>
#include <game/PlayerController.hpp>

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

            void registerStates();
        private:

            sf::RenderWindow    window_;

            StateStack          stateStack_;
            PlayerController    playerController_;
    };

}

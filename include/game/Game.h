#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <resources/ResourceHolder.h>

namespace faod
{

    class Game
    {
        public:
            Game();
            Game(const Game& g) = delete;
            Game& operator=(const Game& g) = delete;
            Game& operator=(const Game&& g) = delete;
            Game(Game&& g) = delete;

            void run();

            static const sf::Time TimePerFrame;

        private:
            void processEvents();
            void update(sf::Time delta);
            void render();

            sf::RenderWindow window_;
            sf::Sprite  player_;
            ResourceHolder<sf::Texture, int> res_;
    };

};

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace faod
{

	class Game
	{
		public:
			Game();
			void run();

			static const sf::Time TimePerFrame;

		private:
			void processEvents();
			void update(sf::Time delta);
			void render();

			sf::RenderWindow window_;
			sf::RectangleShape  player_;
	};

};

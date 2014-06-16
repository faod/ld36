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

		private:
			void processEvents();
			void update();
			void render();

			sf::RenderWindow window_;
			sf::RectangleShape  player_;
	};	
};

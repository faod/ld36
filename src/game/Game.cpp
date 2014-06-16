#include <game/Game.h>
#include <SFML/Window/Event.hpp>

namespace faod
{
	Game::Game() : window_(sf::VideoMode(640, 480), "FAOD Game"), player_(sf::Vector2f(32, 32))
	{
		player_.setPosition(100., 100.);
		player_.setFillColor(sf::Color::Blue);
	}

	void Game::run()
	{
		while(window_.isOpen())
		{
			processEvents();
			update();
			render();
		}

	}


	void Game::processEvents()
	{
		sf::Event event;

		while(window_.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window_.close();
		}

	}

	void Game::update()
	{

	}

	void Game::render()
	{
		window_.clear();
		window_.draw(player_);
		window_.display();
	}


};

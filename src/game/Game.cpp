#include <game/Game.h>
#include <SFML/Window/Event.hpp>

namespace faod
{
	const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

	Game::Game() : window_(sf::VideoMode(640, 480), "FAOD Game"), player_(sf::Vector2f(32, 32))
	{
		player_.setPosition(100., 100.);
		player_.setFillColor(sf::Color::Blue);
	}

	void Game::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while(window_.isOpen())
		{
			processEvents();
			timeSinceLastUpdate += clock.restart();

			while(timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processEvents();
				update(TimePerFrame);
			}
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

	void Game::update(sf::Time delta)
	{
		(void) delta;

	}

	void Game::render()
	{
		window_.clear();
		window_.draw(player_);
		window_.display();
	}


};

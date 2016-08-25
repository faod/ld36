#include <game/Game.h>
#include <SFML/Window/Event.hpp>

namespace faod
{
	const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

	Game::Game() : window_(sf::VideoMode(640, 480), "FAOD Game")
	{
        res_.load(1, "swampman.png");
		player_.setPosition(100., 100.);
		player_.setTexture(res_.get(1));
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

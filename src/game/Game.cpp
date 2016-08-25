#include <game/Game.hpp>
#include <SFML/Window/Event.hpp>

namespace faod
{
    const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


    //Whole game state initialization here. Game class will hold the whole world info
	Game::Game(const std::string& title, unsigned int width, unsigned int height)
        : window_(sf::VideoMode(width, height), title)
	{
        res_.load(1, "swampman.png");
		player_.setPosition(100., 100.);
		player_.setTexture(res_.get(1));
	}

    //Game Mainloop
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


    //Main event processing loop
	void Game::processEvents()
	{
		sf::Event event;

		while(window_.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window_.close();
		}

	}

    //Main logic update loop.
	void Game::update(sf::Time delta)
	{
		(void) delta;

	}

    //Main render loop
	void Game::render()
	{
		window_.clear();
		window_.draw(player_);
		window_.display();
	}


}

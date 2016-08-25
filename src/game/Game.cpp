#include <game/Game.hpp>
#include <SFML/Window/Event.hpp>

namespace faod
{
    const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


    //Whole game state initialization here. Game class will hold the whole world info
	Game::Game(const std::string& title, unsigned int width, unsigned int height)
        :   window_(sf::VideoMode(width, height), title)
          , stateStack_(State::Context(window_))
	{
        registerStates();
	}

    //Game Mainloop
	void Game::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while(window_.isOpen())
		{
            sf::Time delta = clock.restart();
			timeSinceLastUpdate += delta;

			while(timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processInput();
				update(TimePerFrame);

                if(stateStack_.isEmpty())
                {
                    window_.close();
                }
			}
			render();
		}

	}


    //Main event processing loop
	void Game::processInput()
	{
		sf::Event event;

		while(window_.pollEvent(event))
		{
            stateStack_.handleEvent(event);
			if(event.type == sf::Event::Closed)
				window_.close();
		}

	}

    //Main logic update loop.
	void Game::update(sf::Time delta)
	{
		stateStack_.update(delta);

	}

    //Main render loop
	void Game::render()
	{
		window_.clear();

        stateStack_.draw();

        window_.setView(window_.getDefaultView());

		window_.display();
	}

    void Game::registerStates()
    {
        //TODO
    }
}

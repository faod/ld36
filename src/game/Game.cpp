#include <game/Game.hpp>
#include <states/GameState.hpp>
#include <states/TitleState.hpp>

#include <SFML/Window/Event.hpp>

#include <exception>

namespace faod
{
    const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


    //Whole game state initialization here. Game class will hold the whole world info
	Game::Game(const std::string& title, unsigned int width, unsigned int height)
        :   window_(sf::VideoMode(width, height), title)
            ,textures_()
            ,fonts_()
            ,stateStack_(State::Context(window_, textures_, fonts_, maps_, playerController_))
	{
        loadFonts();
        registerStates();

        //Need to push 1st state
        stateStack_.pushState(States::ID::Title);
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

                //Check if statestack was cleared in last update
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
    void Game::loadFonts()
    {
        fonts_.load("pixel", "assets/fonts/SFPixelate.ttf");
    }

    void Game::registerStates()
    {
        stateStack_.registerState(States::ID::Game, &makeBasicStateFactory<GameState>);
        stateStack_.registerState(States::ID::Title, &makeBasicStateFactory<TitleState>);
    }
}

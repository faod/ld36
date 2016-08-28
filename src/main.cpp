#include <game/Game.hpp>

#include <iostream>
#include <exception>

int main(int argc, char *argv[])
{
    (void) argc, (void) argv;

    try
    {
	    faod::Game g("ludum", 800, 600);
        try
        {
            //If the game has loaded successfully
            g.run();
        } catch(std::exception& e)
        {
            std::cerr << "Game has unexpectedly failed: " << e.what() << std::endl;
        }

    } catch(std::exception& e)
    {
        std::cerr << "Failure to launch the game: " << e.what() << std::endl;
    }

	return 0;
}

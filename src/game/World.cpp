#include <game/World.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace faod
{
    World::World(sf::RenderWindow& window) : window_(window), view_(window.getDefaultView())
    {
        (void) window;    
    }

    void World::update(sf::Time delta)
    {
        (void) delta;
        // Gameplay relative update   
    }

    
}

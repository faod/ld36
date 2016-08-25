#include <game/World.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace faod
{
    World::World(sf::RenderWindow& window) : window_(window), view_(window.getDefaultView())
    {
        loadTextures();
        buildScene();
    }

    void World::update(sf::Time delta)
    {
        //update world
            //TODO
            //
            //
        //apply commands
        while(!commandQueue_.isEmpty())
        {
            sceneGraph_.onCommand(commandQueue_.pop(), delta);
        }
        //then scenegraph
        sceneGraph_.update(delta);
    }
    
    void World::draw()
    {
        window_.setView(view_);
        window_.draw(sceneGraph_);
    }
    
    CommandQueue& World::getCommandQueue()
    {
        return commandQueue_;
    }

    void World::loadTextures()
    {
        //TODO
    }

    void World::buildScene()
    {
        //TODO
    }
}

#include <game/World.hpp>
#include <states/GameState.hpp>
#include <objects/Catapult.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace faod
{
    World::World(sf::RenderWindow& window, GameState &state, State::Context context, std::string mapname) 
        : window_(window)
          ,view_(window.getDefaultView())
          ,owningstate_(&state)
          ,context_(context)
          ,map_(nullptr)
    {
        loadMap();
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
        //First thing first, add the catapult
        Catapult::Smart_ptr ptr(new Catapult());
        sceneGraph_.attachChild(std::move(ptr));
    }
    void World::loadMap()
    {

    }
}

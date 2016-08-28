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
          ,mapname_(mapname)
          ,map_(nullptr)
          ,mapList_(context.maps_)
    {
        loadMap();
        loadTextures();
        buildScene();
    }

    void World::update(sf::Time delta)
    {

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
        view_.setCenter(catapult_->getPosition());
        window_.draw(*map_);
        window_.draw(sceneGraph_);
    }

    CommandQueue& World::getCommandQueue()
    {
        return commandQueue_;
    }

    void World::loadTextures()
    {
        //Load catapult spritesheet
        if(!context_.textures_->isIn("catapult"))
        {
            context_.textures_->load("catapult", "assets/sprites/Catapult.png");
        }
    }

    void World::buildScene()
    {
        //First thing first, add the catapult
        catapult_ = new Catapult(context_.textures_->get("catapult"), context_.fonts_);
        Catapult::Smart_ptr ptr(catapult_);
        sceneGraph_.attachChild(std::move(ptr));
    }
    void World::loadMap()
    {
        //If map is not already in the manager
        if(!mapList_->isIn(mapname_))
        {
            mapList_->load(mapname_, mapname_);
        }
        map_ = &mapList_->get(mapname_);
        //continue loading map
    }
}

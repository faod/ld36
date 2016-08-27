#include <states/GameState.hpp>
#include <game/World.hpp>
#include <game/CommandQueue.hpp>
#include <game/PlayerController.hpp>

namespace faod
{
    GameState::GameState(StateStack &stack, Context context)
        : GameState(stack, context, "desert")
    {
    }

    GameState::GameState(StateStack &stack, Context context, std::string mapname) 
        : State(stack , context)
          , world_(new World(*context.window_, *this, context, mapname))
          , playerController_(*context.playerController_)
          , maps_(context.maps_)
          , currentmap_(mapname)
    {
    }

    void GameState::draw()
    {
        world_->draw();
    }

    bool GameState::update(sf::Time delta)
    {
        world_->update(delta);

        CommandQueue& commands = world_->getCommandQueue();
        playerController_.handleRealtimeInput(commands);

        return false;
    }
    bool GameState::handleEvent(const sf::Event& event)
    {
        //Game input handling
        CommandQueue& commands = world_->getCommandQueue();
        playerController_.handleEvent(event, commands);

        return false;
    }
    std::function<State::Smart_ptr()> GameState::makeGameStateString(StateStack& s, Context c, std::string str)
    {
        return [&s, c, str] () { return Smart_ptr(new GameState(s, c, str)); } ;
    }


}

#include <states/GameState.hpp>
#include <game/World.hpp>

namespace faod
{
    GameState::GameState(StateStack &stack, Context context) : State(stack, context) , world_(new World(*context.window_)), playerController_(*context.playerController_)
    {
    }

    void GameState::draw()
    {
        //TODO
    }

    bool GameState::update(sf::Time delta)
    {
        (void) delta;
        return false;
        //TODO
    }
    bool GameState::handleEvent(const sf::Event& event)
    {
        (void) event;
        return false;
        //TODO
    }
}

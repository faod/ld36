#include <states/State.hpp>

#include <states/StateStack.hpp>

namespace faod
{
    State::Context::Context(sf::RenderWindow &window) : window_(&window)
    {
    }

    State::State(StateStack& stack, Context context) : stack_(&stack), context_(context)
    {
    }

    State::~State()
    {
    }
    
    void State::requestStackPush(States::ID stateID)
    {
        stack_->pushState((stateID));
    }

    void State::requestStackPop()
    {
        stack_->popState();
    }

    void State::requestStateClear()
    {
        stack_->clearStates();
    }

    State::Context State::getContext() const
    {
        return context_;
    }
}

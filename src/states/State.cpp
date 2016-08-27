#include <states/State.hpp>

#include <states/StateStack.hpp>

namespace faod
{
    State::Context::Context(sf::RenderWindow &window
                            ,ResourceHolder<sf::Texture, size_t> &textures
                            ,ResourceHolder<sf::Font, std::string> &fonts
                            ,ResourceHolder<tmx::TileMap, std::string> &maps
                            ,PlayerController &player)
        : window_(&window)
          ,textures_(&textures)
          ,fonts_(&fonts)
          ,maps_(&maps)
          ,playerController_(&player)
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

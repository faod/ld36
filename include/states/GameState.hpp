#pragma once

#include <states/State.hpp>

namespace faod
{
    class World;
    class GameState : public State
    {
        public:
            GameState(StateStack& stack, Context context);

            virtual void draw();
            virtual bool update(sf::Time delta);
            virtual bool handleEvent(const sf::Event& event);

        private:
            std::unique_ptr<World>  world_;
            PlayerController&       playerController_;
    };
}    


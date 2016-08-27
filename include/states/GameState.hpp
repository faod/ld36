#pragma once

#include <states/State.hpp>

namespace faod
{
    class World;
    class GameState : public State
    {
        public:
            static std::function<State::Smart_ptr()> makeGameStateString(StateStack& s, State::Context c, std::string str);
        public:
            GameState(StateStack& stack, Context context);
            GameState(StateStack& stack, Context context, std::string str);
            virtual void draw();
            virtual bool update(sf::Time delta);
            virtual bool handleEvent(const sf::Event& event);

        private:
            std::unique_ptr<World>  world_;
            PlayerController&       playerController_;
            ResourceHolder<tmx::TileMap, std::string> *maps_;
    };
}    


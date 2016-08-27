#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <states/State.hpp>
#include <states/StateStack.hpp>

namespace faod
{
    class FooBar: public State
    {
        private:
            sf::Time current = sf::Time::Zero;

        public:
            FooBar(StateStack& stack, Context context): State(stack, context) {};

            virtual void    draw();
            virtual bool    update(sf::Time delta);
            virtual bool    handleEvent(const sf::Event& event);
    };
}

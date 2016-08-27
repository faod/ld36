#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

#include <states/State.hpp>
#include <states/StateStack.hpp>

namespace faod
{
    class TitleState: public State
    {
        private:
            sf::Time current_ = sf::Time::Zero;
            sf::Text menuprompt_;
        public:
            TitleState(StateStack& stack, Context context);

            virtual void    draw();
            virtual bool    update(sf::Time delta);
            virtual bool    handleEvent(const sf::Event& event);
    };
}

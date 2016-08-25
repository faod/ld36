#pragma once

#include <game/Identifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

//forward decl
namespace sf
{
    class RenderWindow;
}

namespace faod
{
    class StateStack;

    class State
    {
        public:
            typedef std::unique_ptr<State> Smart_ptr;
    
            struct Context
            {
                Context(sf::RenderWindow& window);

                sf::RenderWindow* window_;
            };

        public:
                        State(StateStack& stack, Context context);
            virtual     ~State();

            virtual void    draw() = 0;
            virtual bool    update(sf::Time delta) = 0;
            virtual bool    handleEvent(const sf::Event& event) = 0;

        protected:
            //3 methods below are called when requesting stacking/popping of a state. 
            void    requestStackPush(States::ID stateID);
            void    requestStackPop();
            void    requestStateClear();

            Context getContext() const;

        private:
            StateStack*     stack_;
            Context         context_;
    };
}

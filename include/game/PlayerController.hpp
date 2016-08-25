#pragma once


#include <game/Command.hpp>
#include <SFML/Window/Event.hpp>

#include <map>

namespace faod
{
    class CommandQueue;

    class PlayerController
    {
        public:
            enum class Action
            {
                Idle
            };
        public:
            PlayerController();


            void handleEvent(const sf::Event& event, CommandQueue& commands);
            void handleRealtimeInput(CommandQueue& commands);

            void assignKey(Action action, sf::Keyboard::Key key);
            sf::Keyboard::Key   getAssignedKey(Action action) const;

        private:
            static bool     isRealtimeAction(Action action);
            void            initializeActions();

        private:
            std::map<sf::Keyboard::Key, Action>     keyBinding_;
            std::map<Action, Command>               actionBinding_;
    };
}

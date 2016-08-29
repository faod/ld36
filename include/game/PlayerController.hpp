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
                Idle,
                Forward,
                Backward,
                LeftSteer,
                RightSteer,
                Throw
            };
        public:
            PlayerController();


            void handleEvent(const sf::Event& event, CommandQueue& commands);
            void handleRealtimeInput(CommandQueue& commands);

            //Assign key to action
            void assignKey(Action action, sf::Keyboard::Key key);
            //returns key assiociated with given action. sf::Keyboard::Unknown if not bound
            sf::Keyboard::Key   getAssignedKey(Action action) const;
            //returns current action assiociated with given key
            Action getAssociatedAction(sf::Keyboard::Key key) const;

        private:
            static bool     isRealtimeAction(Action action);
            void            initializeActions();

        private:
            std::map<sf::Keyboard::Key, Action>     keyBinding_;
            std::map<Action, Command>               actionBinding_;
    };
}

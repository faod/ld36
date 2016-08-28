#include <game/PlayerController.hpp>

#include <game/CommandQueue.hpp>

#include <objects/Catapult.hpp>
#include <game/Identifiers.hpp>

namespace faod
{
    PlayerController::PlayerController()
    {
        //initial key bindings
        keyBinding_[sf::Keyboard::Left]     = Action::LeftSteer;
        keyBinding_[sf::Keyboard::Right]    = Action::RightSteer;
        keyBinding_[sf::Keyboard::Up]       = Action::Forward;
        keyBinding_[sf::Keyboard::Down]     = Action::Backward;

        //initial actions binding
        initializeActions();

        //proper categories
        for(auto &bind : actionBinding_)
        {
            bind.second.category_ = Category::Catapult;
        }
    }

    void PlayerController::handleEvent(const sf::Event& event, CommandQueue& commands)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            //Check if pressed key appears in registered keys, trigger command if so
            auto found = keyBinding_.find(event.key.code);
            if(found != keyBinding_.end() && !isRealtimeAction(found->second))
            {
                commands.push(actionBinding_[found->second]);
            }
        }
    }

    void PlayerController::handleRealtimeInput(CommandQueue& commands)
    {
        //Go through all assigned keys and check if pressed
        for(auto pair : keyBinding_)
        {
            if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            {
                commands.push(actionBinding_[pair.second]);
            }
        }
    }

    bool PlayerController::isRealtimeAction(Action action)
    {
        switch(action)
        {
            case Action::Idle:
            case Action::LeftSteer:
            case Action::RightSteer:
            case Action::Forward:
            case Action::Backward:
                return true;
            default:
                return false;
        };
    }
    void PlayerController::assignKey(Action action, sf::Keyboard::Key key)
    {
        //Remove all keys that are already mapped to an action
        for(auto itr = keyBinding_.begin() ; itr != keyBinding_.end(); )
        {
            if(itr->second == action)
            {
                keyBinding_.erase(itr++);
            }
            else
                ++itr;
        }
        //Insert new binding
        keyBinding_[key] = action;
    }

    sf::Keyboard::Key PlayerController::getAssignedKey(Action action) const
    {
        for(auto pair : keyBinding_)
        {
            if(pair.second == action)
            {
                return pair.first;
            }
        }
        return sf::Keyboard::Unknown;
    }
    PlayerController::Action PlayerController::getAssociatedAction(sf::Keyboard::Key key) const
    {
        for(auto pair : keyBinding_)
        {
            if(pair.first == key)
            {
                return pair.second;
            }
        }
        return Action::Idle;
    }

    void PlayerController::initializeActions()
    {
        actionBinding_[Action::LeftSteer].action_ = derivedAction<Catapult>
                (std::bind(&Catapult::moveInput, std::placeholders::_1, sf::Vector2f(-100.,0.),std::placeholders::_2));
        actionBinding_[Action::RightSteer].action_ = derivedAction<Catapult>
                (std::bind(&Catapult::moveInput, std::placeholders::_1, sf::Vector2f(100.,0.),std::placeholders::_2));
        actionBinding_[Action::Forward].action_ = derivedAction<Catapult>
                (std::bind(&Catapult::moveInput, std::placeholders::_1, sf::Vector2f(0.,-100.),std::placeholders::_2));
        actionBinding_[Action::Backward].action_ = derivedAction<Catapult>
                (std::bind(&Catapult::moveInput, std::placeholders::_1, sf::Vector2f(0.,100.),std::placeholders::_2));
    }
}

#include <states/StateStack.hpp>

#include <cassert>

namespace faod
{
    StateStack::StateStack(State::Context context) : stack_(), context_(context), factories_(), pendingList_()
    {
    }
    
    void StateStack::pushState(States::ID stateID)
    {
        pendingList_.push_back(PendingChange(Action::Push, stateID));
    }

    void StateStack::popState()
    {   
        pendingList_.push_back(PendingChange(Action::Pop));
    }

    void StateStack::clearStates()
    {
        pendingList_.push_back(PendingChange(Action::Clear));
    }

    bool StateStack::isEmpty() const
    {
        return stack_.empty();
    }

    void StateStack::draw()
    {
        //Draw all active states from bottom to top
        for(State::Smart_ptr& state :  stack_)
        {
            state->draw();
        }
    }

    void StateStack::update(sf::Time delta)
    {
        //Iterate frop top to bottom until update() returns false

        for(auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
        {
            if(!(*itr)->update(delta))
            {
                break;
            }
        }

        //we can now applyPendingChange (eventually pop out a state) without breaking itr
        applyPendingChanges();
    }

    void StateStack::handleEvent(const sf::Event& event)
    {
        //Iterate from top to bottom until handleEvent() returns false
        for(auto itr = stack_.rbegin(); itr != stack_.rend(); itr++)
        {
            if(!(*itr)->handleEvent(event))
            {
                break;
            }
        }
    }

    State::Smart_ptr StateStack::createState(States::ID stateID)
    {
        auto found = factories_.find(stateID);
        assert(found != factories_.end() && "Attempt to create a state whithout associated factory");

        return found->second();
    }

    void StateStack::applyPendingChanges()
    {
        for(PendingChange change : pendingList_)
        {   
            switch(change.action)
            {
                case Action::Push:
                    stack_.push_back(createState(change.stateID));
                    break;
                case Action::Pop:
                    stack_.pop_back();
                    break;
                case Action::Clear:
                    stack_.clear();
                    break;

                default: assert(false);     
            }
        }
        pendingList_.clear();
    }
    
    StateStack::PendingChange::PendingChange(Action act, States::ID id) : action(act), stateID(id)
    {
    }
}

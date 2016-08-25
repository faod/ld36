#pragma once

#include <vector>
#include <map>

#include <states/State.hpp>

namespace faod
{
    class StateStack
    {
        public:
            StateStack(const StateStack& s) = delete;
            StateStack& operator=(const StateStack &s) = delete;
            StateStack& operator=(StateStack &&s)  = delete;
            StateStack(StateStack &&s) = delete;

        public:
            explicit StateStack(State::Context context);


            //Associates a state ID with a state factory
            template <typename T>
            void    registerState(States::ID stateID);
           
            void    update(sf::Time delta);
            void    draw();
            void    handleEvent(const sf::Event& event);

            void    pushState(States::ID stateID);
            void    popState();
            void    clearStates();
            
            bool    isEmpty() const;

        private:
            State::Smart_ptr    createState(States::ID stateID);
            void                applyPendingChanges();         

        private:
            enum class Action
            {
                Push,
                Pop,
                Clear,
            };

            struct PendingChange
            {
                explicit PendingChange(Action action, States::ID stateID = States::None);

                Action      action;
                States::ID  stateID;
            };
        private:
            std::vector<State::Smart_ptr>                               stack_;
            
            State::Context                                              context_;
            std::map<States::ID, std::function<State::Smart_ptr()>>     factories_; 

            std::vector<PendingChange>                                  pendingList_;
    };


    //template method definition
    
    template<typename T>
    void StateStack::registerState(States::ID stateID)
    {
        /* Register a State havin stateID ID. type T is type of State.
         *
         */
        factories_[stateID] = [this] () { return State::Smart_ptr(new T(*this, context_)); };
    }

}

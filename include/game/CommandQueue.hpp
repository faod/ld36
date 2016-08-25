#pragma once

#include <game/Command.hpp>

#include <queue>

namespace faod
{
    class CommandQueue
    {
        public:
            void        push(const Command& command);
            Command     pop();
            bool        isEmpty() const;

        private:
            std::queue<Command>     queue_;
    };
}

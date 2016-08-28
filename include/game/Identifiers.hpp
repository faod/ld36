#pragma once

namespace faod
{

    //ID used by the statestack
    namespace States
    {
        enum class ID
        {
            None,
            Title,
            Menu,
            Game,
            Loading,
            Pause
        };
    }

    namespace Category
    {
        enum Type
        {
            None        =   0,
            Scene       =   1,
            Catapult    =   1 << 1,
        };
    }

}

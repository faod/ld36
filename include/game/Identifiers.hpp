#pragma once

namespace faod
{

    //ID used by the statestack
    namespace States
    {
        enum ID
        {
            None, 
            Title, 
            Menu,
            Game,
            Loading,
            Pause
        };
    }

}

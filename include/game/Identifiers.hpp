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

    namespace Collision
    {
        enum Type
        {
            None        = 0,
            Catapult    = 1,
            Projectile  = 1 << 1,
            Bonus       = 1 << 2,
            Foe         = 1 << 3,
            Destroyable = 1 << 4,
            Solid       = 1 << 5,
            Poison      = 1 << 6
        };
    }

}

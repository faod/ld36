#include <objects/Catapult.hpp>

namespace faod
{
    Catapult::Catapult()
        :CollidableObject(ConvexHull(0)) //FIXME
        ,hp_(100)
        ,ammo_(3)
        ,forcemax_(initialforcemax_)
    {
    }
}

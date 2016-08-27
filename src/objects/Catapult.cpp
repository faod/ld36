#include <objects/Catapult.hpp>

namespace faod
{
    const float Catapult::forcemin_ = 1.;
    const float Catapult::initialforcemax_ = 2.;

    Catapult::Catapult()
        :CollidableObject(ConvexHull(0)) //FIXME
        ,hp_(100)
        ,ammo_(3)
        ,forcemax_(initialforcemax_)
    {
    }
}

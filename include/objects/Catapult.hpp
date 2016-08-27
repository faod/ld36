#pragma once

#include <objects/CollidableObject.hpp>

namespace faod
{
    class Catapult : public CollidableObject
    {
        public:
            Catapult();

        private:
            static const float forcemin_; 
            static const float initialforcemax_;

        private:
            unsigned int hp_;
            unsigned int ammo_;
            float forcemax_;
    };
    const float Catapult::forcemin_ = 1.;
    const float Catapult::initialforcemax_ = 2.;
}

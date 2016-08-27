#pragma once

#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include <cmath>

namespace faod
{
    class HSL
    {
        public:
            int Hue;
            float Saturation;
            float Luminance;

            HSL();
            HSL(int H, float S, float L);

            sf::Color toRGB();
    };
}

#include <utils/HSL.hpp>
#include <cmath>

static float hsl_to_rgb_helper(float x, float a, float b)
{
    if (x < 0)
    {
        x += 1;
    }
    if (x > 1) 
    {
        x -= 1;
    }

    if (x * 6 < 1)
    {
        return b + (a - b) * 6 * x;
    }
    if (x * 6 < 3)
    {
        return a;
    }
    if (x * 6 < 4)
    {
        return b + (a - b) * (4.0 - 6.0 * x);
    }
    return b;
}

static int hsl_to_rgb(float hue, float saturation, float lightness)
{
    float a, b, h;

    hue = (int)hue % 360;
    if (hue < 0)
    {
        hue += 360;
    }
    h = hue / 360;

    if (lightness < 0.5)
    {
        a = lightness + lightness * saturation;
    }
    else
    {
        a = lightness + saturation - lightness * saturation;
    }
    b = lightness * 2 - a;

    int res = 0xFF << 8;
    res |= (int)std::floor(0xFF * hsl_to_rgb_helper(h + 1.0 / 3.0, a, b));
    res <<= 8;
    res |= (int)std::floor(0xFF * hsl_to_rgb_helper(h, a, b));
    res <<= 8;
    res |= (int)std::floor(0xFF * hsl_to_rgb_helper(h - 1.0 / 3.0, a, b));
    return res;
}


namespace faod
{

    HSL::HSL(): Hue(0), Saturation(0), Luminance(0) {}

    HSL::HSL(int H, float S, float L): Hue(H), Saturation(S), Luminance(L) {}

    sf::Color HSL::toRGB()
    {
        return sf::Color(hsl_to_rgb(Hue, Saturation, Luminance));
    }
}

#include "Tcolor.h"
#include <algorithm>
Tcolor::Tcolor()
    :r(0),g(0),b(0)
{

}

Tcolor::Tcolor(int red, int green, int blue)
    :r(red),g(green),b(blue)
{
    r = std::min(255,r);
    g = std::min(255,g);
    b = std::min(255,b);
}

Tcolor::~Tcolor()
{

}

Tcolor Tcolor::operator +(const Tcolor &color) const
{
    return Tcolor(this->r + color.r,this->g + color.g, this->b + color.b);
}

Tcolor Tcolor::operator *(const Tcolor &color) const
{
    float red = 1.0*r/255,green=1.0*g/255,blue = 1.0*b/255;
    float red1 = 1.0*color.r/255,green1=1.0*color.g/255,blue1 = 1.0*color.b/255;
    return Tcolor(red*red1*255,green * green1*255, blue * blue1*255);
}

Tcolor Tcolor::operator *(const float factor) const
{
    return modulate (factor);
}

Tcolor Tcolor::operator +=(const Tcolor &color)
{
    r += color.r;
    r = std::min(255,r);
    g += color.g;
    g = std::min(255,g);
    b += color.b;
    b = std::min(255,b);
    return (* this);
}

Tcolor Tcolor::modulate(float f) const
{
    int red = r * f;
    int green = g * f;
    int blue = b *f;
    return Tcolor(red,green, blue);
}


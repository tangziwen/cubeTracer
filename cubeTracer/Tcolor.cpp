#include "Tcolor.h"
#include <algorithm>


Tcolor::Tcolor()
    :r(0),g(0),b(0)
{

}

Tcolor::Tcolor(float red, float green, float blue)
    :r(red),g(green),b(blue)
{
    r = std::min(red,1.0f);
    g = std::min(green,1.0f);
    b = std::min(blue,1.0f);
}

Tcolor::~Tcolor()
{

}

Tcolor Tcolor::operator +(const Tcolor &color) const
{

    return  Tcolor(this->r + color.r,this->g + color.g, this->b + color.b);
}

Tcolor Tcolor::operator *(const Tcolor &color) const
{
    return Tcolor(r*color.r,g * color.g, b * color.b);
}

Tcolor Tcolor::operator *(const float factor) const
{
    return modulate (factor);
}

Tcolor Tcolor::operator +=(const Tcolor &color)
{
    r += color.r;
    g += color.g;
    b += color.b;
    return (* this);
}

Tcolor Tcolor::operator /(float f) const
{
    return Tcolor(r / f, g / f, b /f);
}

Tcolor Tcolor::modulate(float f) const
{
    float red = r * f;
    float green = g * f;
    float blue = b *f;
    return Tcolor(red,green, blue);
}

int Tcolor::redInt()
{
    return int(r*255);
}

int Tcolor::blueInt()
{
    return int(b * 255);
}

int Tcolor::greenInt()
{
    return int (g * 255);
}

float Tcolor::luminance()
{
    return r *0.299 + g* 0.587 + b*0.114;
}


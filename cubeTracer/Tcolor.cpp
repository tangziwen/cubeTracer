#include "Tcolor.h"

Tcolor::Tcolor()
    :r(0),g(0),b(0)
{

}

Tcolor::Tcolor(int red, int green, int blue)
    :r(red),g(green),b(blue)
{

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
    return Tcolor(this->r * color.r,this->g * color.g, this->b * color.b);
}

Tcolor Tcolor::modulate(float f) const
{
        return Tcolor(this->r * f,this->g * f, this->b * f);
}


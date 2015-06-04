#ifndef TCOLOR_H
#define TCOLOR_H


class Tcolor
{
public:
    Tcolor();
    Tcolor(float red, float green, float blue);
    ~Tcolor();
    Tcolor operator + (const Tcolor & color) const;
    Tcolor operator * (const Tcolor & color) const;
    Tcolor operator * (const float factor) const;
    Tcolor operator +=(const Tcolor & color);
    Tcolor modulate(float f)const;
    float luminance();
    float r,g,b;
};

#endif // TCOLOR_H

#ifndef TBASELIGHT_H
#define TBASELIGHT_H

#include "tvector.h"
#include "Tcolor.h"
class Tscene;
class TexplicitLight
{
public:
    TexplicitLight();
    ~TexplicitLight();
    virtual Tvector getDir(Tvector pos);
    virtual float getIntensity(int direction);
    virtual bool isVisible(Tvector pos,Tscene * scene);
    virtual Tcolor getIrradiance(Tvector pos,Tvector normal, Tscene *scene);
};

#endif // TBASELIGHT_H


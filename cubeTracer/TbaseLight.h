#ifndef TBASELIGHT_H
#define TBASELIGHT_H

#include <QVector3D>
#include "Tcolor.h"
class Tscene;
class TexplicitLight
{
public:
    TexplicitLight();
    ~TexplicitLight();
    virtual QVector3D getDir(QVector3D pos);
    virtual float getIntensity(int direction);
    virtual bool isVisible(QVector3D pos,Tscene * scene);
    virtual Tcolor getIrradiance(QVector3D pos,QVector3D normal, Tscene *scene);
};

#endif // TBASELIGHT_H


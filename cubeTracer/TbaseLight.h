#ifndef TBASELIGHT_H
#define TBASELIGHT_H

#include <QVector3D>
class Tscene;
class TbaseLight
{
public:
    TbaseLight();
    ~TbaseLight();
    virtual float getIntensity(int direction) = 0;
    virtual float getIrradiance(QVector3D pos,QVector3D normal, Tscene *scene) = 0;
};

#endif // TBASELIGHT_H


#ifndef TDIRECTIONALLIGHT_H
#define TDIRECTIONALLIGHT_H
#include <qvector3d.h>
#include "TbaseLight.h"
#include "Tcolor.h"
class TdirectionalLight :public TbaseLight
{
public:
    TdirectionalLight(QVector3D dir,float maxIntensity,Tcolor color);
    ~TdirectionalLight();
    virtual float getIntensity(int direction);
    virtual float getIrradiance(QVector3D pos,QVector3D normal,Tscene * scene);
private:
    QVector3D m_dir;
    Tcolor m_color;
    float m_maxIntensity;
};

#endif // TDIRECTIONALLIGHT_H

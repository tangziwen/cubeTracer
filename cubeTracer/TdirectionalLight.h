#ifndef TDIRECTIONALLIGHT_H
#define TDIRECTIONALLIGHT_H
#include <qvector3d.h>
#include "TbaseLight.h"
#include "Tcolor.h"
class TdirectionalLight :public TexplicitLight
{
public:
    TdirectionalLight(QVector3D dir,float maxIntensity,Tcolor color);
    ~TdirectionalLight();
    virtual bool isVisible(QVector3D pos,Tscene * scene);
    virtual float getIntensity(int direction);
    virtual Tcolor getIrradiance(QVector3D pos,QVector3D normal,Tscene * scene);
    Tcolor color() const;
    void setColor(const Tcolor &color);
    virtual QVector3D getDir(QVector3D pos);
private:
    QVector3D m_dir;
    Tcolor m_color;
    float m_maxIntensity;
};

#endif // TDIRECTIONALLIGHT_H

#ifndef TPLANE_H
#define TPLANE_H

#include "TintersectionResult.h"
#include "TbaseGeometry.h"
#include <QVector3D>
class Tplane : public TbaseGeometry
{
public:
    Tplane(QVector3D normal,float dist);
    ~Tplane();
    virtual TintersectionResult getIntersect(const Tray & ray);
private:
    QVector3D m_normal;
    QVector3D m_pos;
    float m_dist;
};

#endif // TPLANE_H

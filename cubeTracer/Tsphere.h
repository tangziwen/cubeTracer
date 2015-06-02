#ifndef TSPHERE_H
#define TSPHERE_H
#include <QVector3D>
#include "TbaseGeometry.h"

class Tsphere : public TbaseGeometry
{
public:
    Tsphere(float radius, QVector3D center);
    ~Tsphere();
    float radius() const;
    void setRadius(float radius);

    QVector3D center() const;
    void setCenter(QVector3D center);

    virtual TintersectionResult getIntersect(const Tray & ray);

private:
    void updateSqrRadius();
private:
    float m_radius;
    QVector3D m_center;
    float m_sqrRadius;
};

#endif // TSPHERE_H

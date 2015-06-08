#ifndef TSPHERE_H
#define TSPHERE_H
#include "tvector.h"
#include "TbaseGeometry.h"

class Tsphere : public TbaseGeometry
{
public:
    Tsphere(float radius, Tvector center);
    ~Tsphere();
    float radius() const;
    void setRadius(float radius);

    Tvector center() const;
    void setCenter(Tvector center);

    virtual TintersectionResult getIntersect(const Tray & ray);

    virtual float getIntensity(int direction);
    virtual bool isVisible(Tvector pos,Tscene * scene);
    virtual Tcolor getIrradiance(Tvector pos,Tvector normal, Tscene *scene);
    virtual Tvector getDir(Tvector pos);
    virtual GeometryType getType();
private:
    void updateSqrRadius();
private:
    float m_radius;
    Tvector m_center;
    float m_sqrRadius;
};

#endif // TSPHERE_H

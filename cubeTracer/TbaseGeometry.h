#ifndef TBASEGEOMETRY_H
#define TBASEGEOMETRY_H

#include "TintersectionResult.h"
#include "Tray.h"
#include "Tmaterial.h"
#include "TbaseLight.h"

class TbaseGeometry
{
public:
    enum class GeometryType
    {
        Sphere,
        Plane,
        Undefined
    };

    TbaseGeometry();
    ~TbaseGeometry();
    virtual TintersectionResult getIntersect(const Tray & ray) = 0;
    Tmaterial *material() const;
    void setMaterial(Tmaterial *material);
    virtual GeometryType getType();

    virtual void getRandomPosInSurface(Tvector & pos, Tvector &normal);
private:
    Tmaterial * m_material;
};

#endif // TBASEGEOMETRY_H

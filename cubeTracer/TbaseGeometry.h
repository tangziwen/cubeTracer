#ifndef TBASEGEOMETRY_H
#define TBASEGEOMETRY_H

#include "TintersectionResult.h"
#include "Tray.h"
#include "Tmaterial.h"
class TbaseGeometry
{
public:
    TbaseGeometry();
    ~TbaseGeometry();
    virtual TintersectionResult getIntersect(const Tray & ray) = 0;
    Tmaterial *material() const;
    void setMaterial(Tmaterial *material);

private:
    Tmaterial * m_material;
};

#endif // TBASEGEOMETRY_H

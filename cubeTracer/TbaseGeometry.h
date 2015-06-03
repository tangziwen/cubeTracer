#ifndef TBASEGEOMETRY_H
#define TBASEGEOMETRY_H

#include "TintersectionResult.h"
#include "Tray.h"
#include "Tmaterial.h"
#include "TbaseLight.h"

class TbaseGeometry : public TbaseLight
{
public:
    TbaseGeometry();
    ~TbaseGeometry();
    virtual TintersectionResult getIntersect(const Tray & ray) = 0;
    Tmaterial *material() const;
    void setMaterial(Tmaterial *material);
    virtual bool isLight() const;
    virtual void setIsLight(bool isLight);

private:
    Tmaterial * m_material;
    bool m_isLight;
};

#endif // TBASEGEOMETRY_H

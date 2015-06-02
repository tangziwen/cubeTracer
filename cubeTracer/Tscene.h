#ifndef TSCENE_H
#define TSCENE_H

#include "TbaseGeometry.h"
#include "TintersectionResult.h"
#include "Tray.h"
#include <vector>
#include "TbaseLight.h"
class Tscene
{
public:
    Tscene();
    ~Tscene();
void addGeometry(TbaseGeometry * g);
void addLight(TbaseLight * light);
TintersectionResult intersect(const Tray & ray);
std::vector<TbaseLight *> & getLightList();
private:
std::vector<TbaseGeometry *> m_geometryList;
std::vector<TbaseLight *> m_lightList;
};

#endif // TSCENE_H

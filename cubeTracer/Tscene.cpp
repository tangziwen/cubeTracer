#include "Tscene.h"

Tscene::Tscene()
{

}

Tscene::~Tscene()
{

}

void Tscene::addGeometry(TbaseGeometry *g)
{
    m_geometryList.push_back (g);
}

void Tscene::addLight(TexplicitLight *light)
{
    m_lightList.push_back (light);
}

TintersectionResult Tscene::intersect(const Tray &ray)
{
    auto minDistance = 999999.0f;
    auto minResult = TintersectionResult::getNotHit ();
    for(int i =0;i<m_geometryList.size ();i++)
    {
        TbaseGeometry * g = m_geometryList[i];
        auto result =g->getIntersect (ray);
        if (result.geometry ()&& result.distance ()< minDistance) {
            minDistance = result.distance();
            minResult = result;
        }
    }
    return minResult;
}

std::vector<TexplicitLight *> &Tscene::getLightList()
{
    return m_lightList;
}



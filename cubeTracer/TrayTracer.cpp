#include "TrayTracer.h"

#include <algorithm>

static QVector3D reflect(QVector3D dir,QVector3D normal)
{
    auto reflectDirFactor =2 * QVector3D::dotProduct (normal,dir);
    auto tmp = normal;
    tmp *= reflectDirFactor;
    auto reflectDir = dir - tmp;
    return reflectDir;
}

TrayTracer::TrayTracer(int width, int height, Tcamera *camera, Tscene *scene)
    :m_bufferWidth(width),m_bufferHeight(height),m_camera(camera),m_scene(scene)
{
    m_data = new Tcolor[m_bufferWidth * m_bufferHeight];
}

TrayTracer::~TrayTracer()
{

}

void TrayTracer::setPixelAt(int x, int y, Tcolor col)
{
    m_data[y*m_bufferWidth + x ] = col;
}

Tcolor TrayTracer::getPixelAt(int x, int y)
{
    return m_data[y*m_bufferWidth + x ];
}

void TrayTracer::generate(TrayTracer::Policy policy)
{
    for (int y = 0; y < m_bufferHeight; y++) {
        auto sy = 1- 1.0*y / m_bufferHeight;
        for (int x = 0; x < m_bufferWidth; x++) {
            auto sx = 1.0*x / m_bufferWidth;
            auto ray = camera()->generateRay(sx, sy);
            Tcolor color(0,0,0);
            switch(policy)
            {
            case Policy::CUSTOM:
                break;
            case Policy::DEPTH:
                color = handleDepth (ray);
                break;
            case Policy::DIRECT_LIGHT:
                break;
            case Policy::RAY_TRACING_EXPLICIT_LIGHT:
                color = radianceWithExplicitLight(ray,1);
                break;
            case Policy::NORMAL:
                color = handleNormal(ray);
                break;
            }
            setPixelAt (x,y,color);
        }
    }
}
int TrayTracer::bufferWidth() const
{
    return m_bufferWidth;
}

void TrayTracer::setBufferWidth(int bufferWidth)
{
    m_bufferWidth = bufferWidth;
}
int TrayTracer::bufferHeight() const
{
    return m_bufferHeight;
}

void TrayTracer::setBufferHeight(int bufferHeight)
{
    m_bufferHeight = bufferHeight;
}
Tcamera *TrayTracer::camera() const
{
    return m_camera;
}

void TrayTracer::setCamera(Tcamera *camera)
{
    m_camera = camera;
}
Tscene *TrayTracer::scene() const
{
    return m_scene;
}

void TrayTracer::setScene(Tscene *scene)
{
    m_scene = scene;
}
#ifdef QT_VERSION

QImage *TrayTracer::getQImage()
{
    auto qimage = new QImage(m_bufferWidth,m_bufferHeight,QImage::Format_RGB32);
    for(int y =0;y<m_bufferHeight;y++)
    {
        for(int x= 0;x<m_bufferWidth;x++)
        {
            auto color = getPixelAt (x,y);
            qimage->setPixel (x,y,qRgb(255*color.r,255*color.g,255*color.b));
        }
    }
    return qimage;
}

#endif


#define MIN(a, b) (a>b?b:a)
Tcolor TrayTracer::handleDepth(Tray ray)
{
    Tcolor col(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto depth = 1.0f - MIN((result.distance () / camera()->far ()),1.0f);
        col.r = depth;
        col.g = depth;
        col.b = depth;
    }
    return col;
}

Tcolor TrayTracer::handleNormal(Tray ray)
{
    Tcolor col(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto normal = result.normal ();
        col.r = normal.x() *0.5 + 0.5;
        col.g = normal.y() *0.5 + 0.5;
        col.b = normal.z() *0.5 + 0.5;
    }
    return col;
}

Tcolor TrayTracer::radianceWithExplicitLight(Tray ray,int reflectLevel)
{
    Tcolor finalColor(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto material = result.geometry ()->material ();
        if(!material) return finalColor;

        Tcolor selfColor = material->sampleSelfColor ();

        //**********Emission.
        auto emissionColor = selfColor*material->emission ();

        //reflect
        Tcolor reflectColor;
        auto allLights = scene()->getLightList();
        for(int i =0;i<allLights.size ();i++)
        {
            TexplicitLight * light = allLights[i];

            if(!light->isVisible (result.pos (),scene())) continue;
            //get the irradiance from the explicit light source.
            auto lightDir = light->getDir (result.pos ());
            auto lightRadiance = light->getIrradiance (result.pos (),result.normal (),scene());

            reflectColor += lightRadiance * material->BRDF (ray.direction (),lightDir,result.normal ());
        }

        //ideal specular radiance from other object.
        if(material->reflectiveness () > 0 && reflectLevel > 0)
        {
            // get the ideal specular ray.
            auto reflectVec = reflect(ray.direction (),result.normal ());
            auto reflectRay = Tray(result.pos (),reflectVec);

            auto idealSpecularRadiance = radianceWithExplicitLight(reflectRay,reflectLevel - 1);
            reflectColor +=idealSpecularRadiance * material->BRDF (ray.direction (),reflectVec,result.normal ());
        }

        //render euqation.
        finalColor = emissionColor+ selfColor*reflectColor*material->reflectiveness ();
    }
    return finalColor;
}






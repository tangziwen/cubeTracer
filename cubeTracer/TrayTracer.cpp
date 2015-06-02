#include "TrayTracer.h"

#include <algorithm>
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
            case Policy::NAIVE:
                color = handleNaive (ray);
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
            qimage->setPixel (x,y,qRgb(color.r,color.g,color.b));
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
        auto depth = 255 - MIN((result.distance () / camera()->far ()) * 255,255);
        col.r = depth;
        col.g = depth;
        col.b = depth;
    }
    return col;
}

Tcolor TrayTracer::handleNaive(Tray ray)
{
    return handleNaiveRecursive(ray,3);
}

Tcolor TrayTracer::handleNormal(Tray ray)
{
    Tcolor col(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto normal = result.normal ();
        col.r = (normal.x ()+1)*128;
        col.g = (normal.y ()+1)*128;
        col.b = (normal.z ()+1)*128;
    }
    return col;
}

Tcolor TrayTracer::handleNaiveRecursive(Tray ray,int reflectLevel)
{
    Tcolor finalColor(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto material = result.geometry ()->material ();
        if(!material) return finalColor;

        //diffuse
        Tcolor diffuseColor(0,0,0);
        auto allLights = scene()->getLightList();
        for(int i =0;i<allLights.size ();i++)
        {
            TbaseLight * light = allLights[i];
            auto irradiance = light->getIrradiance (result.pos (),result.normal (),scene());
            diffuseColor = diffuseColor +(material->diffuseColor () *material->sampleTexture (ray,result.pos (),result.normal ())).modulate (material->diffuse () * irradiance);
        }


        //specular

        //reflect
        Tcolor reflectColor;
        if(material->reflectiveness () > 0 && reflectLevel > 0)
        {
            // get the reflect
            auto reflectDirFactor =2 * QVector3D::dotProduct (result.normal (),ray.direction ());
            auto tmp = result.normal ();
            tmp *= reflectDirFactor;
            auto reflectDir = ray.direction () - tmp;
            auto reflectRay = Tray(result.pos (),reflectDir);
            reflectColor = handleNaiveRecursive(reflectRay,reflectLevel - 1).modulate (material->reflectiveness ());
        }
        finalColor = diffuseColor + reflectColor;
    }
    return finalColor;
}






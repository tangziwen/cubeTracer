#include "TrayTracer.h"

#include <algorithm>

#include "tvector.h"

#include "TbaseMath.h"

static Tvector reflect(Tvector dir,Tvector normal)
{
    auto reflectDirFactor =2 * Tvector::dotProduct (normal,dir);
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

Tcolor TrayTracer::getPixelAt(int index)
{
    return m_data[index];
}

Tcolor TrayTracer::getPixelAt(int x, int y)
{
    return m_data[y*m_bufferWidth + x ];
}

void TrayTracer::generate(TrayTracer::Policy policy)
{
    for (int y = 0; y < m_bufferHeight; y++) {
        fprintf(stderr,"\rRendering: %5.2f%% .",100.0f*y/(m_bufferHeight));
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
            case Policy::NORMAL:
                color = handleNormal(ray);
                break;
            case Policy::RAY_TRACING_EXPLICIT_LIGHT:
                color = radianceWithExplicitLight(ray,3);
                break;
            case Policy::PATH_TRACING:
            {
                int sampleNums = 200;
                for(int sampeIndex = 0; sampeIndex < sampleNums; sampeIndex ++)
                {
                    color += radiancePathTracer(ray,3) / (1.0f *sampleNums);
                }
            }
                break;
            }
            setPixelAt (x,y,color);
        }
    }
    printf("\nGenearted.\n");
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

void TrayTracer::writeToFile(const char *fileName)
{
    printf("Writing the result to the %s image file.\n",fileName);
    FILE *f = fopen(fileName, "w");         // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", m_bufferWidth, m_bufferWidth, 255);
    for (int i=0; i<m_bufferWidth*m_bufferHeight; i++)
    {
        auto c = getPixelAt (i);
        fprintf(f,"%d %d %d ",c.redInt (),c.blueInt (),c.greenInt ());
    }
    fclose(f);
    printf("Done.\n");
}

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
    if(reflectLevel <= 0)
        return Tcolor(0,0,0);
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

            reflectColor += lightRadiance * material->BRDF (-ray.direction (),-lightDir,result.normal ());
        }

        //ideal specular radiance from other object.
        if(material->reflectiveness () > 0)
        {

            // get the ideal specular ray.
            auto reflectVec = reflect(ray.direction (),result.normal ());
            auto reflectRay = Tray(result.pos (),reflectVec);

            auto idealSpecularRadiance = radianceWithExplicitLight(reflectRay,reflectLevel - 1);
            reflectColor +=idealSpecularRadiance * material->BRDF (-ray.direction (),reflectVec,result.normal ());
        }

        //render euqation.
        finalColor = emissionColor+ selfColor*reflectColor*material->reflectiveness ();
    }
    return finalColor;
}

Tcolor TrayTracer::radiancePathTracer(Tray ray, int reflectLevel)
{
    if(reflectLevel <=0) return Tcolor(0,0,0);
    auto result = scene()->intersect(ray);
    if (result.geometry()) {
        auto material = result.geometry ()->material ();
        auto emissionColor = material->sampleSelfColor () * material->emission ();
        auto reflectColor = Tcolor(0,0,0);
        switch(material->getType ())
        {
        case Tmaterial::MaterialType::Mirror://ideal specular object.
        {
            auto reflectVec = reflect(ray.direction (),result.normal ());
            auto reflectRay = Tray(result.pos (),reflectVec);
            auto idealSpecularRadiance = radiancePathTracer(reflectRay,reflectLevel - 1);
            reflectColor +=idealSpecularRadiance * material->BRDF (-ray.direction (),reflectVec,result.normal ());
        }
            break;
        case Tmaterial::MaterialType::Light://ideal emission object.
        {
            reflectColor = Tcolor(0,0,0);
        }
            break;
        case Tmaterial::MaterialType::BlinnPhong:
        {

        }
            break;
        case Tmaterial::MaterialType::Diffuse:
        {
            Tvector nl;
            if(Tvector::dotProduct (result.normal (),ray.direction ())<0)
            {
                nl = result.normal ();
            }else
            {
                nl = result.normal ().negatived();
            }

            double r1=2*TbaseMath::PI*TbaseMath::randF ();
            double r2=TbaseMath::randF ();
            double r2s=sqrt(r2);
            Tvector w=nl;
            Tvector u;
            if(fabs(w.x())>0.1)
            {
                u = Tvector(0,1,0);
            }else
            {
                u = Tvector(1,0,0);
            }
            u = Tvector::crossProduct (u,w);
            u.normalize ();
            Tvector v=Tvector::crossProduct (w,u);
            Tvector dir = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).normalized();
            reflectColor = radiancePathTracer(Tray(result.pos (),dir),reflectLevel - 1);
        }
            break;
        }
        return emissionColor + material->selfColor () * reflectColor * material->reflectiveness ();
    }
    return Tcolor(0,0,0);
}






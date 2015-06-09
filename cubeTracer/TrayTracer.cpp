#include "TrayTracer.h"
#include <time.h>
#include <string.h>
#include <algorithm>

#include "tvector.h"

#include "TbaseMath.h"
inline void getElapseTime(clock_t start, clock_t end, char * str)
{
    clock_t totalSces = (end - start)/CLOCKS_PER_SEC;
    clock_t tmp = totalSces;
    clock_t elapse_time[3] ={0,0,0};
    for(int i = 2;i>=0;i--)
    {
        elapse_time[i] = tmp%60;
        tmp /= 60;
    }
    char tmpStr[100] = {0};
    if(elapse_time[0])
    {
        sprintf(tmpStr,"%ld hours, ",elapse_time[0]);
        strcat(str,tmpStr);
    }
    if(elapse_time[1])
    {
        sprintf(tmpStr,"%ld minutes, ",elapse_time[1]);
        strcat(str,tmpStr);
    }
    //always show the seconds.
    sprintf(tmpStr,"%ld seconds.\n",elapse_time[2]);
    strcat(str,tmpStr);
}


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

void TrayTracer::generate(TrayTracer::Policy policy,int samplesPerPixel)
{
    clock_t start = clock();
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
            case Policy::PATH_TRACING_UNIDIR:
            {
                for(int sampeIndex = 0; sampeIndex < samplesPerPixel; sampeIndex ++)
                {
                    color += radiancePathTraceUni(ray,6) / (1.0f *samplesPerPixel);
                }
            }
                break;
            case Policy::PATH_TRACING_BIDIR:
            {
                for(int sampeIndex = 0; sampeIndex < samplesPerPixel; sampeIndex ++)
                {
                    //get eye path.
                    std::vector<Tvector> eyePath;// the path from the eye.
                    eyePath.push_back (ray.origin ());//first add ray origin
                    getPath(ray,4,&eyePath);

                    //get light path
                    std::vector<Tvector> lightPath;// the path from a random light.
                    auto randomLight = scene()->getRandomLight();//get random light.
                    Tvector lightPos,lightNormal;
                    randomLight->getRandomPosInSurface (lightPos, lightNormal);//get random pos in random light.
                    //add the light pos
                    lightPath.push_back (lightPos);
                    Tray lightFirstRay(lightPos,TbaseMath::uniformHemisphericalVector (lightNormal));
                    getPath(lightFirstRay,4,&lightPath);

                    //try to concat them,get the final light path.
                    concatEyeAndLight(&eyePath,&lightPath);
                    //get the radiance according the final light path.
                    color += radiancePathTraceBi (ray,&eyePath)/ (1.0f *samplesPerPixel);
                }
            }
                break;
            }
            setPixelAt (x,y,color);
        }
    }
    clock_t end = clock();
    char durationStr[100] ={0};
    getElapseTime (start,end,durationStr);
    printf("\nGenearted.\n");
    printf("last %s",durationStr);
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
        fprintf(f,"%d %d %d ",c.redInt (),c.greenInt (),c.blueInt ());
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

Tcolor TrayTracer::radiancePathTraceUni(Tray ray, int reflectLevel)
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
            auto idealSpecularRadiance = radiancePathTraceUni(reflectRay,reflectLevel - 1);
            auto cosineFactor = Tvector::dotProduct (reflectVec,result.normal ());
            reflectColor +=idealSpecularRadiance * material->BRDF (-ray.direction (),reflectVec,result.normal ())*cosineFactor;
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

            auto cosineFactor = Tvector::dotProduct (dir,result.normal ());
            reflectColor = radiancePathTraceUni(Tray(result.pos (),dir),reflectLevel - 1) * material->BRDF (ray.direction ().negatived (),dir,result.normal ())*cosineFactor;
        }
            break;
        }
        return emissionColor + material->selfColor () * reflectColor * material->reflectiveness ();
    }
    return Tcolor(0,0,0);
}

void TrayTracer::getPath(Tray fromRay, int reflectLevel, std::vector<Tvector> *verticesList)
{
     if(reflectLevel <=0) return;
     auto result = scene()->intersect(fromRay);
     if(result.geometry ())
     {
         //add this surface position to vertices list.
         verticesList->push_back (result.pos ());
         auto material = result.geometry ()->material ();
         switch(material->getType ())
         {
         case Tmaterial::MaterialType::Mirror://ideal specular object.
         {
             auto reflectVec = reflect(fromRay.direction (),result.normal ());
             auto reflectRay = Tray(result.pos (),reflectVec);
             getPath(reflectRay,reflectLevel -1 ,verticesList);
         }
             break;
         case Tmaterial::MaterialType::Light://ideal emission object.
         {
         }
             break;
         case Tmaterial::MaterialType::BlinnPhong:
         {

         }
             break;
         case Tmaterial::MaterialType::Diffuse:
         {
             Tvector nl;
             if(Tvector::dotProduct (result.normal (),fromRay.direction ())<0)
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
             getPath(Tray(result.pos (),dir),reflectLevel -1 ,verticesList);
         }
             break;
         }
     }
}

Tcolor TrayTracer::radiancePathTraceBi(Tray ray, std::vector<Tvector> *path)
{
    auto result = scene()->intersect(ray);
    path->erase (path->begin ());//remove first.
    if(result.geometry ())
    {
        auto material = result.geometry ()->material ();
        if(path->size () >1)
        {
            Tvector reflectDir = path->at (1) - result.pos ();
            reflectDir.normalize ();
            Tray reflectRay(result.pos (),reflectDir);
            return  material->sampleSelfColor ()*material->emission ()+ material->sampleSelfColor () * radiancePathTraceBi(reflectRay,path)*material->BRDF (ray.direction ().negatived (),reflectRay.direction (),result.normal ());
        }
        else
        {
            return material->sampleSelfColor () * material->emission ();
        }
    }
}

void TrayTracer::concatEyeAndLight(std::vector<Tvector> *eye, std::vector<Tvector> *light)
{

    std::vector <Tvector> tmp;
    for(int i =0;i<eye->size ();i++)
    {
        tmp.push_back (eye->at(i));
        for(int j =0;j<light->size();j++)
        {
            Tray ray(light->at(j),eye->at(i) - light->at(j));
            auto result = scene ()->intersect (ray);
            if(!result.geometry ())//can arrive?
            {
                for(int k = j; k>=0;k--)//merge the light path and eye path
                {
                    tmp.push_back (light->at(k));
                }
                goto FINISH;
            }
        }
    }
FINISH:
    eye->clear ();
    for(int i =0;i<tmp.size ();i++)
    {
        eye->push_back (tmp[i]);
    }
}






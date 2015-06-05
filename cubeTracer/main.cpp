#include "Tscene.h"
#include "Tsphere.h"
#include "Tcamera.h"
#include "TrayTracer.h"
#include "Tplane.h"
#include "TdirectionalLight.h"
#include "TblinnPhongMaterial.h"
#include "TmirrorMaterial.h"
#include "TlightMaterial.h"
#include "TdiffuseMaterial.h"
#include <stdio.h>
#include <string.h>


//little test case
void sceneForRayTracer(Tscene * scene)
{
    auto plane = new Tplane(Tvector(0,1,0), 0);
    plane->setMaterial (new TdiffuseMaterial);
    plane->material ()->setSelfColor (Tcolor(0.3,0.3,0.3));

    auto sphere = new Tsphere(5,Tvector(-6, 10, -10));
    sphere->setMaterial (new TblinnPhongMaterial(1,4));
    sphere->material ()->setSelfColor (Tcolor(1,0,0));

    auto sphere1 = new Tsphere(5,Tvector(6, 10, -10));
    sphere1->setMaterial (new TmirrorMaterial());
    sphere1->material ()->setSelfColor (Tcolor(1,1,1));
    sphere1->material ()->BRDF (Tvector(-0.5,0.5,0),Tvector(-0.5,-0.5,0),Tvector(0,1,0));

    auto sphere3 = new Tsphere(4,Tvector(5,10,2));
    sphere3->setMaterial (new TlightMaterial());
    sphere3->material ()->setSelfColor (Tcolor(0,0,1));

    auto sun = new TdirectionalLight(Tvector(0,-1,-1),1,Tcolor(1,1,1));

    scene->addLight (sun);
    scene->addGeometry (sphere);
    scene->addGeometry (sphere1);
    scene->addGeometry (sphere3);
    scene->addGeometry (plane);
}

void sceneForPathTracing(Tscene * scene)
{
    auto plane = new Tplane(Tvector(0,1,0), 0);
    plane->setMaterial (new TdiffuseMaterial);
    plane->material ()->setSelfColor (Tcolor(0.3,0.3,0.3));

    auto sphere3 = new Tsphere(4,Tvector(0,5,0));
    sphere3->setMaterial (new TlightMaterial());
    sphere3->material ()->setSelfColor (Tcolor(0,0,1));

    scene->addGeometry (sphere3);
    scene->addGeometry (plane);
}

int main(int argc, char *argv[])
{

    printf("The cubeTracer ver 0.1\n");

    auto camera = new Tcamera(Tvector(0, 10, 20), Tvector(0, 0, -1),  Tvector(0, 1, 0), 60,20);
    auto scene = new Tscene();




    TrayTracer tracer(640,480,camera,scene);

    switch(argc)
    {
    case 1:
    {
        sceneForPathTracing(scene);
        tracer.generate (TrayTracer::Policy::RAY_TRACING_EXPLICIT_LIGHT);
        tracer.writeToFile ("./out.ppm");
    }
        break;
    case 2:
    {
        if(strcmp (argv[1],"-h"))
        {
            printf("usage: cubeTracer -n out.ppm\n");
        }else if(strcmp (argv[1],"-v"))
        {
            printf("version 0.01 \n");
        }
    }
        break;
    case 3:
    {
        if(strcmp(argv[1],"-n"))
        {
            sceneForRayTracer(scene);
            tracer.generate (TrayTracer::Policy::RAY_TRACING_EXPLICIT_LIGHT);
        }else if(false)
        {

        }
    }
        tracer.writeToFile (argv[2]);
        break;
    }
    return 0;
}

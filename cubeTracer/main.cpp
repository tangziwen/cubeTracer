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
    //bottom
    auto bottom = new Tplane(Tvector(0,1,0), 0);
    bottom->setMaterial (new TdiffuseMaterial);
    bottom->material ()->setSelfColor (Tcolor(0.3,0.3,1));

    //left
    auto left = new Tplane(Tvector(1,0,0), -10);
    left->setMaterial (new TdiffuseMaterial);
    left->material ()->setSelfColor (Tcolor(1,0.1,0.1));

    //right
    auto right = new Tplane(Tvector(-1,0,0), -10);
    right->setMaterial (new TdiffuseMaterial);
    right->material ()->setSelfColor (Tcolor(0.1,1,0.1));

    //back
    auto back = new Tplane(Tvector(0,0,1), -20);
    back->setMaterial (new TdiffuseMaterial);
    back->material ()->setSelfColor (Tcolor(0.5,0.5,0.5));

    //top
    auto top = new Tplane(Tvector(0,-1,0), -20);
    top->setMaterial (new TlightMaterial);
    top->material ()->setSelfColor (Tcolor(0.8,0.8,0.8));

    //front
    auto front = new Tplane(Tvector(0,0,-1), -30);
    front->setMaterial (new TdiffuseMaterial);
    front->material ()->setSelfColor (Tcolor(1,0.8,0.8));

    auto lightBult = new Tsphere(4,Tvector(0,23,-5));
    lightBult->setMaterial (new TlightMaterial());
    lightBult->material ()->setSelfColor (Tcolor(1,1,1));

    auto mirrorSphere = new Tsphere(4,Tvector(3,10,-5));
    mirrorSphere->setMaterial (new TmirrorMaterial());
    mirrorSphere->material ()->setSelfColor (Tcolor(1,1,1));

    scene->addGeometry (lightBult);

    scene->addGeometry (right);
    scene->addGeometry (bottom);
    scene->addGeometry (back);
    scene->addGeometry (left);
    scene->addGeometry (top);
    scene->addGeometry (front);
    scene->addGeometry (mirrorSphere);
}

int main(int argc, char *argv[])
{

    printf("The cubeTracer ver 0.1\n");

    auto camera = new Tcamera(Tvector(0, 10, 20), Tvector(0, 0, -1),  Tvector(0, 1, 0), 60,20);
    auto scene = new Tscene();




    TrayTracer tracer(640,640,camera,scene);

    switch(argc)
    {
    case 1:
    {
        sceneForPathTracing(scene);
        tracer.generate (TrayTracer::Policy::PATH_TRACING);
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

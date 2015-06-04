
#include <QApplication>
#include "softWarePainter.h"

#include "Tscene.h"
#include "Tsphere.h"
#include "Tcamera.h"
#include "TrayTracer.h"
#include "Tplane.h"
#include "TdirectionalLight.h"
#include "TblinnPhongMaterial.h"
#include "TglassyMaterial.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    softWarePainter painter;
    auto camera = new Tcamera(Tvector(0, 10, 20), Tvector(0, 0, -1),  Tvector(0, 1, 0), 60,20);

    auto scene = new Tscene();

    auto plane = new Tplane(Tvector(0,1,0), 0);
    plane->setMaterial (new TblinnPhongMaterial(1,4));
    plane->material ()->setSelfColor (Tcolor(0.3,0.3,0.3));

    auto sphere = new Tsphere(5,Tvector(-6, 10, -10));
    sphere->setMaterial (new TblinnPhongMaterial(1,4));
    sphere->material ()->setSelfColor (Tcolor(1,0,0));

    auto sphere1 = new Tsphere(5,Tvector(6, 10, -10));
    sphere1->setMaterial (new TmirrorMaterial());
    sphere1->material ()->setSelfColor (Tcolor(1,1,1));
    sphere1->material ()->BRDF (Tvector(-0.5,0.5,0),Tvector(-0.5,-0.5,0),Tvector(0,1,0));

    auto sphere3 = new Tsphere(1,Tvector(5,10,2));
    sphere3->setMaterial (new TblinnPhongMaterial(1,4));
    sphere3->material ()->setSelfColor (Tcolor(0,0,1));

    auto sun = new TdirectionalLight(Tvector(0,-1,-1),1,Tcolor(1,1,1));

    scene->addLight (sun);
    scene->addGeometry (sphere);
    scene->addGeometry (sphere1);
    scene->addGeometry (sphere3);
    scene->addGeometry (plane);


    TrayTracer tracer(640,480,camera,scene);
    tracer.generate (TrayTracer::Policy::RAY_TRACING_EXPLICIT_LIGHT);
    painter.show ();
    painter.setImage (tracer.getQImage ());
    painter.setFixedSize (640,480);
    return a.exec();
}

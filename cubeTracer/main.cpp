
#include <QApplication>
#include "softWarePainter.h"

#include "Tscene.h"
#include "Tsphere.h"
#include "Tcamera.h"
#include "TrayTracer.h"
#include "Tplane.h"
#include "TdirectionalLight.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    softWarePainter painter;
    auto camera = new Tcamera(QVector3D(0, 10, 10), QVector3D(0, 0, -1),  QVector3D(0, 1, 0), 90,20);

    auto scene = new Tscene();

    auto plane = new Tplane(QVector3D(0,1,0), 0);
    plane->setMaterial (new Tmaterial(0,1,0,Tcolor(128,128,128)));
    auto sphere = new Tsphere(5,QVector3D(-6, 10, -10));
    sphere->setMaterial (new Tmaterial(0.6,0.4,0,Tcolor(255,0,255)));
    auto sphere1 = new Tsphere(5,QVector3D(6, 10, -10));
    sphere1->setMaterial (new Tmaterial(0.5,0.5,0,Tcolor(0,0,255)));

    auto sphere2 = new Tsphere(2,QVector3D(0, 10, -4));
    sphere2->setMaterial (new Tmaterial(0.4,0.6,0,Tcolor(255,0,0)));

    auto sphere3 = new Tsphere(1,QVector3D(5,13,2));
    sphere3->setMaterial (new Tmaterial(0,0,1,Tcolor(255,255,255)));
    sphere3->setIsLight (true);
    auto sun = new TdirectionalLight(QVector3D(0,-1,-1),1,Tcolor(255,255,255));

    //scene->addLight (sun);
    scene->addGeometry (sphere);
    scene->addGeometry (sphere1);
    scene->addGeometry (sphere2);
    scene->addGeometry (sphere3);
    scene->addGeometry (plane);


    TrayTracer tracer(640,480,camera,scene);
    tracer.generate (TrayTracer::Policy::NAIVE);
    painter.show ();
    painter.setImage (tracer.getQImage ());
    painter.setFixedSize (640,480);
    return a.exec();
}

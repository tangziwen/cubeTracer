#ifndef TRAYTRACER_H
#define TRAYTRACER_H

#include "Tcamera.h"
#include "Tscene.h"
#include "Tcolor.h"

class TrayTracer
{
public:

    enum class Policy
    {
        RAY_TRACING_EXPLICIT_LIGHT,
        DEPTH,
        NORMAL,
        DIRECT_LIGHT,
        PATH_TRACING,
        CUSTOM
    };

    TrayTracer(int width,int height, Tcamera * camera, Tscene * scene);

    ~TrayTracer();

    void setPixelAt(int x,int y,Tcolor col);

    Tcolor getPixelAt(int index);

    Tcolor getPixelAt(int x,int y);

    void generate(Policy policy);

    int bufferWidth() const;

    void setBufferWidth(int bufferWidth);

    int bufferHeight() const;

    void setBufferHeight(int bufferHeight);

    Tcamera *camera() const;

    void setCamera(Tcamera *camera);

    Tscene *scene() const;

    void setScene(Tscene *scene);

    void writeToFile(const char * fileName);
private:
    Tcolor handleDepth(Tray ray);

    Tcolor handleNormal(Tray ray);

    Tcolor radianceWithExplicitLight(Tray ray, int reflectLevel);

    Tcolor radiancePathTracer(Tray ray, int reflectLevel);

private:
    int m_bufferWidth;
    int m_bufferHeight;
    Tcamera * m_camera;
    Tscene * m_scene;
    Tcolor * m_data;
};

#endif // TRAYTRACER_H

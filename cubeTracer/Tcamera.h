#ifndef TCAMERA_H
#define TCAMERA_H

#include <QVector3D>
#include "Tray.h"

class Tcamera
{
public:
    Tcamera(QVector3D eye,QVector3D front,QVector3D upRef,float fov,float far);
    ~Tcamera();
    void init();

    QVector3D eye() const;
    void setEye(const QVector3D &eye);

    QVector3D upRef() const;
    void setUpRef(const QVector3D &upRef);

    QVector3D front() const;
    void setFront(const QVector3D &front);

    QVector3D up() const;
    void setUp(const QVector3D &up);

    QVector3D right() const;
    void setRight(const QVector3D &right);

    float fovScale() const;
    void setFovScale(float fovScale);

    float fov() const;
    void setFov(float fov);

    Tray generateRay(float x, float y);
    float far() const;
    void setFar(float far);

private:
    QVector3D m_eye;
    QVector3D m_upRef;
    QVector3D m_front;
    QVector3D m_up;
    QVector3D m_right;
    float m_fovScale;
    float m_fov;
    float m_far;
};

#endif // TCAMERA_H

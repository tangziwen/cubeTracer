#include "Tcamera.h"
#include <math.h>
Tcamera::Tcamera(QVector3D eye, QVector3D front, QVector3D upRef, float fov, float far)
    :m_eye(eye),m_front(front),m_upRef(upRef),m_fov(fov),m_far(far)
{
    init();
}

Tcamera::~Tcamera()
{

}

void Tcamera::init()
{
    this->m_right = QVector3D::crossProduct (m_front,m_upRef);
    m_up = QVector3D::crossProduct (m_right,m_front);
    m_fovScale = tan(m_fov * 0.5 * 3.14 / 180) * 2;
}
float Tcamera::fov() const
{
    return m_fov;
}

void Tcamera::setFov(float fov)
{
    m_fov = fov;
}

Tray Tcamera::generateRay(float x, float y)
{
    auto r = this->right ();
    r *= (x - 0.5) * this->fovScale ();
    auto u = this->up ();
    u *= (y - 0.5)* this->fovScale ();
    auto direction = this->front () + r + u;
    direction.normalize ();
    return Tray(this->eye(), direction);
}
float Tcamera::far() const
{
    return m_far;
}

void Tcamera::setFar(float far)
{
    m_far = far;
}


float Tcamera::fovScale() const
{
    return m_fovScale;
}

void Tcamera::setFovScale(float fovScale)
{
    m_fovScale = fovScale;
}

QVector3D Tcamera::right() const
{
    return m_right;
}

void Tcamera::setRight(const QVector3D &right)
{
    m_right = right;
}

QVector3D Tcamera::up() const
{
    return m_up;
}

void Tcamera::setUp(const QVector3D &up)
{
    m_up = up;
}

QVector3D Tcamera::front() const
{
    return m_front;
}

void Tcamera::setFront(const QVector3D &front)
{
    m_front = front;
}

QVector3D Tcamera::upRef() const
{
    return m_upRef;
}

void Tcamera::setUpRef(const QVector3D &upRef)
{
    m_upRef = upRef;
}

QVector3D Tcamera::eye() const
{
    return m_eye;
}

void Tcamera::setEye(const QVector3D &eye)
{
    m_eye = eye;
}



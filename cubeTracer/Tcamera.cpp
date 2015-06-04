#include "Tcamera.h"
#include <math.h>
Tcamera::Tcamera(Tvector eye, Tvector front, Tvector upRef, float fov, float far)
    :m_eye(eye),m_front(front),m_upRef(upRef),m_fov(fov),m_far(far)
{
    init();
}

Tcamera::~Tcamera()
{

}

void Tcamera::init()
{
    this->m_right = Tvector::crossProduct (m_front,m_upRef);
    m_up = Tvector::crossProduct (m_right,m_front);
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

Tvector Tcamera::right() const
{
    return m_right;
}

void Tcamera::setRight(const Tvector &right)
{
    m_right = right;
}

Tvector Tcamera::up() const
{
    return m_up;
}

void Tcamera::setUp(const Tvector &up)
{
    m_up = up;
}

Tvector Tcamera::front() const
{
    return m_front;
}

void Tcamera::setFront(const Tvector &front)
{
    m_front = front;
}

Tvector Tcamera::upRef() const
{
    return m_upRef;
}

void Tcamera::setUpRef(const Tvector &upRef)
{
    m_upRef = upRef;
}

Tvector Tcamera::eye() const
{
    return m_eye;
}

void Tcamera::setEye(const Tvector &eye)
{
    m_eye = eye;
}



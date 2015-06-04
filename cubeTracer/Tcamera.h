#ifndef TCAMERA_H
#define TCAMERA_H

#include "tvector.h"
#include "Tray.h"

class Tcamera
{
public:
    Tcamera(Tvector eye,Tvector front,Tvector upRef,float fov,float far);
    ~Tcamera();
    void init();

    Tvector eye() const;
    void setEye(const Tvector &eye);

    Tvector upRef() const;
    void setUpRef(const Tvector &upRef);

    Tvector front() const;
    void setFront(const Tvector &front);

    Tvector up() const;
    void setUp(const Tvector &up);

    Tvector right() const;
    void setRight(const Tvector &right);

    float fovScale() const;
    void setFovScale(float fovScale);

    float fov() const;
    void setFov(float fov);

    Tray generateRay(float x, float y);
    float far() const;
    void setFar(float far);

private:
    Tvector m_eye;
    Tvector m_upRef;
    Tvector m_front;
    Tvector m_up;
    Tvector m_right;
    float m_fovScale;
    float m_fov;
    float m_far;
};

#endif // TCAMERA_H

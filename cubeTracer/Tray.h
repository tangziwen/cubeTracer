#ifndef TRAY_H
#define TRAY_H
#include <QVector3D>

class Tray
{
public:
    Tray(const QVector3D &orgin, const QVector3D & direction);
    ~Tray();
    QVector3D origin() const;
    void setOrigin(const QVector3D &origin);

    QVector3D direction() const;
    void setDirection(const QVector3D &direction);

    QVector3D getPoint(float t) const;
private:
    QVector3D m_origin;
    QVector3D m_direction;
};

#endif // TRAY_H

#ifndef TINTERSECTIONRESULT_H
#define TINTERSECTIONRESULT_H

#include <QVector3D>

class TbaseGeometry;

class TintersectionResult
{
public:
    TintersectionResult();
    ~TintersectionResult();
    QVector3D pos() const;
    void setPos(const QVector3D &pos);

    QVector3D normal() const;
    void setNormal(const QVector3D &normal);

    float distance() const;
    void setDistance(float distance);

    TbaseGeometry *geometry() const;
    void setGeometry(TbaseGeometry *geometry);

    static TintersectionResult getNotHit();
private:
    QVector3D m_pos;
    QVector3D m_normal;
    float m_distance;
    TbaseGeometry * m_geometry;
};

#endif // TINTERSECTIONRESULT_H

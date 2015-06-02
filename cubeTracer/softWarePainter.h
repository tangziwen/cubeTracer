#ifndef SOFTWAREPAINTER_H
#define SOFTWAREPAINTER_H

#include <QWidget>
#include <QImage>
class softWarePainter : public QWidget
{
    Q_OBJECT
public:
    explicit softWarePainter(QWidget *parent = 0);
    ~softWarePainter();
    void setImage(QImage * image);
signals:

public slots:
protected:
    QImage * m_image;
    virtual void paintEvent (QPaintEvent * event);
};

#endif // SOFTWAREPAINTER_H

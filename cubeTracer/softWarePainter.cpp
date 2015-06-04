#include "softWarePainter.h"
#include <QPaintEvent>
#include <QPainter>
softWarePainter::softWarePainter(QWidget *parent) : QWidget(parent),m_image(NULL)
{

}

softWarePainter::~softWarePainter()
{

}

void softWarePainter::setImage(QImage *image)
{
    m_image = image;
}

void softWarePainter::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent (event);
    QPainter painter;
    painter.begin (this);
    if(m_image)
    {
        painter.drawImage (0,0,(*m_image));
    }
    painter.end ();
}


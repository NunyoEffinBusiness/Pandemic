#include "windowarea.h"

WindowArea::WindowArea(QWidget *parent) :
    QMdiArea(parent)
{
    setObjectName("WindowArea");
}

void WindowArea::resizeEvent(QResizeEvent *event)
{
    QMdiArea::resizeEvent(event);
}

void WindowArea::setBackgroundImage(QImage image)
{
    setBackground(image.copy(QRect(0, 38, image.width(), image.height())));
}

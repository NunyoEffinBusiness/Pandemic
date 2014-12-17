#ifndef WINDOWAREA_H
#define WINDOWAREA_H

#include <QBrush>
#include <QColor>
#include <QImage>
#include <QMdiArea>
#include <QResizeEvent>
#include <QWidget>

class WindowArea : public QMdiArea
{
    Q_OBJECT
public:
    explicit WindowArea(QWidget *parent = 0);

    void setBackgroundImage(QImage image);

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:

};

#endif // WINDOWAREA_H

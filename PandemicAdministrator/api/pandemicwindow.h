#ifndef PANDEMICWINDOW_H
#define PANDEMICWINDOW_H

#include <QBitmap>
#include <QDebug>
#include <QCloseEvent>
#include <QColor>
#include <QCursor>
#include <QEvent>
#include <QGridLayout>
#include <QMdiSubWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QResizeEvent>
#include <QShowEvent>
#include <QWidget>
#include "pandemicmodulebase.h"
#include "../widgets/subwindowtitlebar.h"

class PandemicWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    enum ResizePoint{NoEdge = 0x0, LeftEdge = 0x1, BottomEdge = 0x2, RightEdge = 0x4, TopEdge = 0x8};
    explicit PandemicWindow(PandemicModuleBase *module, QWidget *widget = 0);

    const QString package(){ return _package; }
    int hoveredEdges(QMouseEvent *event);

private:
    const PandemicModuleBase *_module;
    const QString _package;
    SubWindowTitleBar *_titleBar;
    QCursor _cursor;
    QWidget *_centralWidget;
    QGridLayout *_centralLayout;
    QPoint _resizePos;
    int _resizePoint;
    bool _resizing;

protected:
    void closeEvent(QCloseEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

signals:

private slots:
    void stateChanged(Qt::WindowStates oldState, Qt::WindowStates newState);

public slots:
    void setMinimumWidth(int width);
    void setMinimumHeight(int height);
    void setMinimumSize(QSize size);
    void setMinimumSize(int width, int height);

};

#endif // PANDEMICWINDOW_H

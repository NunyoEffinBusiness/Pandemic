#ifndef SUBWINDOWTITLEBAR_H
#define SUBWINDOWTITLEBAR_H

#include <QAction>
#include <QBrush>
#include <QColor>
#include <QCursor>
#include <QDebug>
#include <QEvent>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QPushButton>
#include <QSizePolicy>
#include <QStyle>
#include <QStyleOption>
#include <QTime>
#include <QTimer>
#include <QWidget>

class SubWindowTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit SubWindowTitleBar(QMdiSubWindow *window);

private:
    QHBoxLayout *_layout, *_buttonLayout;
    QPushButton *_closeButton, *_minButton, *_maxButton;
    QLabel *_titleLabel;
    bool eventFilter(QObject *object, QEvent *event);

    bool _dragging, _resizing;
    QCursor _cursor;
    QMdiSubWindow *_window;
    QPoint _dragPos, _resizePos;
    QPoint _mouseOffset;
    QWidget *_buttonWidget;

protected:
    void buildWindowButtons();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void adjustTitle();
    void toggleMaximized();
    void windowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState);


};

#endif // SUBWINDOWTITLEBAR_H

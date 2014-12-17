#include "pandemicwindow.h"
#include "../core/application.h"

PandemicWindow::PandemicWindow(PandemicModuleBase *module, QWidget *widget) :
    QMdiSubWindow(), _module(module), _package(module->generateWindowPackage())
{
    setObjectName("PandemicWindow");
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    _cursor = cursor();
    _resizePoint = NoEdge;
    _resizing = false;
    _titleBar = new SubWindowTitleBar(this);

    _centralWidget = new QWidget();
    _centralLayout = new QGridLayout();
    _centralWidget->setLayout(_centralLayout);

    _centralLayout->setSpacing(0);
    _centralLayout->setContentsMargins(0, 1, 0, 0);
    _centralWidget->setObjectName("PandemicWindowContent");

    _centralLayout->addWidget(_titleBar, 0, 0, 1, 1);
    _centralLayout->addWidget(widget, 1, 0, 1, 1);

    layout()->setContentsMargins(8, 0, 8, 8);
    setWidget(_centralWidget);

    setMinimumSize(QSize(widget->sizeHint().width(), widget->sizeHint().height()));
    resize(minimumSize());

    connect(this, SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates)),
            this, SLOT(stateChanged(Qt::WindowStates,Qt::WindowStates)));

}

void PandemicWindow::stateChanged(Qt::WindowStates oldState, Qt::WindowStates newState)
{
    Q_UNUSED(oldState);
    QString color;
    QString border;
    qDebug() << newState;
    if (newState & Qt::WindowActive) color = "#c75050";
    else color = "#bcbcbc";

    if(newState & Qt::WindowMaximized)
    {
        layout()->setContentsMargins(0, 0, 0, 0);
        _titleBar->setFixedHeight(25);
        border = "none";
    }
    else
    {
        layout()->setContentsMargins(8, 0, 8, 8);
        _titleBar->setFixedHeight(30);
        border = "1px solid #666";
    }

    setStyleSheet("#PandemicWindow{ border:" + border + "; } #SubWindowCloseButton{ background:" + color + "; } #SubWindowCloseButton:hover{ background:#e04343; } #SubWindowCloseButton:pressed{ background:#b01919; } #PandemicWindowContent{ border-top:" + border + "; }");
}

int PandemicWindow::hoveredEdges(QMouseEvent *event)
{
    if(minimumSize() == maximumSize()) return NoEdge;

    int edges = NoEdge;

    //left edge
    if(minimumWidth() != maximumWidth() && event->localPos().x() >= 0 && event->localPos().x() <= 8 && event->localPos().y() > 0 && event->localPos().y() <= height())
    {
        edges |= LeftEdge;
    }

    //bottom edge
    if(minimumHeight() != maximumHeight() && event->localPos().x() > 0 && event->localPos().x() < width() && event->localPos().y() > height() - 8 && event->localPos().y() <= height())
    {
        edges |= BottomEdge;
    }

    //right edge
    if(minimumWidth() != maximumWidth() && event->localPos().x() >= width() - 8 && event->localPos().x() <= width() && event->localPos().y() > 0 && event->localPos().y() <= height())
    {
        edges |= RightEdge;
    }

    //top edge
    if(minimumHeight() != maximumHeight() && event->localPos().x() > 0 && event->localPos().x() < width() && event->localPos().y() >= 0 && event->localPos().y() <= 8)
    {
        edges |= TopEdge;
    }

    return edges;
}

void PandemicWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    Application::instance()->closeWindowRequest(this);
}

void PandemicWindow::leaveEvent(QEvent *event)
{
    if(!_resizing) _resizePoint = NoEdge;
}

void PandemicWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(_resizing == true)
    {
        if(_resizePoint & RightEdge)
        {
            resize(event->pos().x() + _resizePos.x(), height());
        }
        if(_resizePoint & BottomEdge)
        {
            resize(width(), event->pos().y() + _resizePos.y());
        }
        if(_resizePoint & LeftEdge)
        {
            QPoint offset = QPoint(event->pos().x() - _resizePos.x(), 0);\
            if(geometry().right() - (pos().x() + offset.x()) > minimumWidth() &&
               geometry().right() - (pos().x() + offset.x()) < maximumWidth()) move(pos() + offset);
            else if(geometry().right() - (pos().x() + offset.x()) > minimumWidth()) move(geometry().right() - (maximumWidth() - 1), pos().y());
            else move(geometry().right() - (minimumWidth() - 1), pos().y());
            resize(width() - offset.x(), height() - offset.y());
        }
        if(_resizePoint & TopEdge)
        {
            QPoint offset = QPoint(0, event->pos().y() - _resizePos.y());
            if(geometry().bottom() - (pos().y() + offset.y()) > minimumHeight() &&
               geometry().bottom() - (pos().y() + offset.y()) < maximumHeight()) move(pos() + offset);
            else if(geometry().bottom() - (pos().y() + offset.y()) > minimumHeight()) move(pos().x(), geometry().bottom() - (maximumHeight() - 1));
            else move(pos().x(), geometry().bottom() - (minimumHeight() - 1));
            resize(width() - offset.x(), height() - offset.y());
        }
    }

    int edges = hoveredEdges(event);
    if(edges == LeftEdge || edges == RightEdge) _cursor.setShape(Qt::SizeHorCursor);
    else if(edges == TopEdge || edges == BottomEdge) _cursor.setShape(Qt::SizeVerCursor);
    else if(edges == (TopEdge | LeftEdge) || edges == (BottomEdge | RightEdge)) _cursor.setShape(Qt::SizeFDiagCursor);
    else if(edges == (BottomEdge | LeftEdge) || edges == (TopEdge | RightEdge)) _cursor.setShape(Qt::SizeBDiagCursor);
    else _cursor.setShape(Qt::ArrowCursor);

    setCursor(_cursor);
}

void PandemicWindow::mousePressEvent(QMouseEvent *event)
{
    _resizePoint = hoveredEdges(event);
    if(event->button() == Qt::LeftButton && _resizePoint)
    {
        if(_resizePoint & RightEdge)
        {
            _resizePos.setX(width() - event->localPos().x());
            qDebug() << "On the right edge";
            _resizing = true;
        }
        if(_resizePoint & BottomEdge)
        {
            _resizePos.setY(height() - event->localPos().y());
            qDebug() << "On the bottom edge";
            _resizing = true;
        }
        if(_resizePoint & LeftEdge)
        {
            _resizePos.setX(event->localPos().x());
            qDebug() << "On the left edge";
            _resizing = true;
        }
    }
    else
        QMdiSubWindow::mousePressEvent(event);
}

void PandemicWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Released" << "_resizing is set to false";
    if( !_resizing)QMdiSubWindow::mouseReleaseEvent(event);
    _resizing = false;
    _resizePoint = NoEdge;
}

void PandemicWindow::paintEvent(QPaintEvent *event)
{
    QMdiSubWindow::paintEvent(event);
}

void PandemicWindow::showEvent(QShowEvent *event)
{
    QMdiSubWindow::showEvent(event);
    _titleBar->adjustTitle();
}

void PandemicWindow::setMinimumWidth(int width)
{
    if(width < 168) width = 168;
    QMdiSubWindow::setMinimumWidth(width);
}

void PandemicWindow::setMinimumHeight(int height)
{
    if(height < 50) height = 50;
    QMdiSubWindow::setMinimumHeight(height);
}

void PandemicWindow::setMinimumSize(QSize size)
{
    setMinimumWidth(size.width());
    setMinimumHeight(size.height());
}

void PandemicWindow::setMinimumSize(int width, int height) { setMinimumSize(QSize(width, height)); }

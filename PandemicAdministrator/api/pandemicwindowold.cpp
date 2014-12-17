#include "pandemicwindow.h"
#include "../core/application.h"
#include "pandemicmodule.h"

PandemicWindow::PandemicWindow(PandemicModuleBase *module, QString name, QWidget *widget) :
    QMdiSubWindow(), _module(module), _package(module->package() + "." + name)
{
    _module = module;
    _widget = 0;
    _initialized = false;

    _titleBar = new SubWindowTitleBar(this);

    _cWidget = new QWidget();
    _pWidget = new QWidget();
    _pWidget->setObjectName("SubWindowContainer");
    _cLayout = new QGridLayout();
    _pLayout = new QGridLayout();
    _cLayout->setContentsMargins(8, 0, 8, 8);
    _pLayout->setContentsMargins(8, 8, 8, 8);
    _cLayout->setSpacing(0);
    _pLayout->setSpacing(0);
    _cWidget->setLayout(_cLayout);
    _pWidget->setLayout(_pLayout);

    _cLayout->addWidget(_titleBar, 0, 0, 1, 1, Qt::AlignTop);
    if(widget) _cLayout->addWidget(_pWidget, 1, 0, 1, 1, Qt::AlignTop);

    setWidget(_cWidget);

    if(widget) setWidget(widget);

    setWindowTitle(module->title());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

void PandemicWindow::setWidget(QWidget *widget)
{
    if(!_initialized)
    {
        QMdiSubWindow::setWidget(widget);
        _initialized = true;
        return;
    }

    if(!_widget && widget)
    {
        _pLayout->addWidget(widget, 0, 0, 1, 1, Qt::AlignTop);
        _widget = widget;

        qDebug() << "Widget set!";
    }
}

void PandemicWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    ((Application *) ((PandemicModule *) _module)->application())->closeWindowRequest(this);
}

void PandemicWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), QColor("#999"));

    QMdiSubWindow::paintEvent(event);
}

void PandemicWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    qDebug() << height();
    if(_pWidget)
        _pWidget->setFixedHeight(height() - (_titleBar->height() + 8));
}


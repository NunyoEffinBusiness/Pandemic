#include "subwindowtitlebar.h"
#include "../api/pandemicwindow.h"

SubWindowTitleBar::SubWindowTitleBar(QMdiSubWindow *window) :
    QWidget(window)
{
    setObjectName("SubWindowTitleBar");
    _dragging = false;
    _resizing = false;
    _window = window;
    _cursor = cursor();

    _layout = new QHBoxLayout();
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    _titleLabel = new QLabel(window->windowTitle());
    _titleLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _titleLabel->setAlignment(Qt::AlignCenter);
    _titleLabel->installEventFilter(this);
    _titleLabel->setMouseTracking(true);
    //_titleLabel->setStyleSheet("background:#ff0000;");

    _buttonWidget = new QWidget();
    _buttonLayout = new QHBoxLayout();
    _buttonLayout->setContentsMargins(0, 0, 0, 0);
    _buttonLayout->setSpacing(1);
    _buttonWidget->setLayout(_buttonLayout);
    _buttonWidget->setFixedWidth(100);

    _closeButton = new QPushButton("");
    _closeButton->setObjectName("SubWindowCloseButton");
    _closeButton->setIcon(QIcon(":/icons/close.png"));
    _closeButton->setIconSize(QSize(10, 10));

    _minButton = new QPushButton("");
    _minButton->setObjectName("SubWindowTitleBarButton");
    _minButton->setIcon(QIcon(":/icons/minimize.png"));
    _minButton->setIconSize(QSize(10, 10));

    _maxButton = new QPushButton("");
    _maxButton->setObjectName("SubWindowTitleBarButton");
    _maxButton->setIcon(QIcon(":/icons/maximize.png"));
    _maxButton->setIconSize(QSize(10, 10));
    _maxButton->setEnabled(true);

    _buttonLayout->addWidget(_minButton);
    _buttonLayout->addWidget(_maxButton);
    _buttonLayout->addWidget(_closeButton);
    _layout->addWidget(_titleLabel);
    _layout->addWidget(_buttonWidget);

    _buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    _layout->setAlignment(_titleLabel, Qt::AlignVCenter);
    _layout->setAlignment(_buttonWidget, Qt::AlignRight);

    setMinimumWidth(50);
    setFixedHeight(30);

    connect(window, SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates)), this, SLOT(windowStateChanged(Qt::WindowStates,Qt::WindowStates)));
    connect(window, SIGNAL(windowTitleChanged(QString)), _titleLabel, SLOT(setText(QString)));
    connect(_maxButton, SIGNAL(clicked()), this, SLOT(toggleMaximized()));
    connect(_closeButton, SIGNAL(clicked()), window, SLOT(close()));
}

bool SubWindowTitleBar::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick && !_resizing && !_dragging)
        toggleMaximized();

    else if(event->type() == QEvent::MouseMove && !_resizing && !_dragging)
    {
        //qDebug() << "Moving...";
        QMouseEvent *e = (QMouseEvent *) event;
        if(e->localPos().y() >= 0 && e->localPos().y() <= 5 && !(_window->windowState() & Qt::WindowMaximized))
        {
            _cursor.setShape(Qt::SizeVerCursor);
            setCursor(_cursor);
            return true;
        }
        else
        {
            _cursor.setShape(Qt::ArrowCursor);
            setCursor(_cursor);
        }
        return false;
    }
    else if(event->type() == QEvent::Leave)
    {
        _cursor.setShape(Qt::ArrowCursor);
        setCursor(_cursor);
        return true;
    }
    event->accept();
    return false;
}

void SubWindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(_resizing && !(_window->windowState() & Qt::WindowMaximized))
    {
        QPoint offset = QPoint(0, event->pos().y() - _resizePos.y());
        if(_window->geometry().bottom() - (_window->pos().y() + offset.y()) > _window->minimumHeight() &&
           _window->geometry().bottom() - (_window->pos().y() + offset.y()) < _window->maximumHeight()) _window->move(_window->pos() + offset);
        else if(_window->geometry().bottom() - (_window->pos().y() + offset.y()) > _window->minimumHeight()) _window->move(_window->pos().x(), _window->geometry().bottom() - (_window->maximumHeight() - 1));
        else _window->move(_window->pos().x(), _window->geometry().bottom() - (_window->minimumHeight() - 1));
        _window->resize(_window->width() - offset.x(), _window->height() - offset.y());
    }
    else if(_dragging)
    {
        _cursor.setShape(Qt::ArrowCursor);
        setCursor(_cursor);
        if(!(_window->windowState() & Qt::WindowMaximized))
        {
            QPoint pos = QPoint(event->pos().x() - _mouseOffset.x(), event->pos().y() - _mouseOffset.y());
            _window->move(_window->pos() + pos);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void SubWindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->localPos().y() >= 0 && event->localPos().y() <= 5)
    {
        _resizing = true;
        _resizePos.setY(event->localPos().y());
    }
    else
    {
        qDebug() << "Mouse Pressed";
        _dragging = true;
        _dragPos = _window->pos();
        _mouseOffset = QPoint(event->localPos().x(), event->localPos().y());
    }
    QWidget::mousePressEvent(event);
}

void SubWindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    _dragging = false;
    _resizing = false;
    QWidget::mouseReleaseEvent(event);
}

void SubWindowTitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);

    adjustTitle();
}

void SubWindowTitleBar::adjustTitle()
{
    _titleLabel->resize(width() - 100, _titleLabel->sizeHint().height());
    if(width() - 100 <= _titleLabel->sizeHint().width()) _titleLabel->setAlignment(Qt::AlignLeft);
    else _titleLabel->setAlignment(Qt::AlignCenter);
}

void SubWindowTitleBar::toggleMaximized()
{
    if(_window->windowState() & Qt::WindowMaximized)
        _window->setWindowState(_window->windowState() & ~Qt::WindowMaximized);
    else
        _window->setWindowState(_window->windowState() | Qt::WindowMaximized);
}

void SubWindowTitleBar::windowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState)
{
    if(newState & Qt::WindowMaximized)
    {
        _maxButton->setIcon(QIcon(":/icons/restore.png"));
        _titleLabel->setFixedHeight(24);
    }
    else
    {
        _maxButton->setIcon(QIcon(":/icons/maximize.png"));
        _titleLabel->setFixedHeight(30);
    }
}

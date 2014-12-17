#include "taskbar.h"
#include "../core/application.h"

TaskBar::TaskBar(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("TaskBar");
    setClockMode(StandardTime);

    _layout = new QGridLayout();
    _layout->setContentsMargins(30, 0, 30, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    buildStartButton();
    buildClock();


    _moduleMapper = new QSignalMapper(this);
    connect(_moduleMapper, SIGNAL(mapped(QString)), Application::instance(), SLOT(runModule(QString)));

    setFixedHeight(38);

    qDebug() << "Taskbar created!";
}

void TaskBar::buildStartButton()
{
    _startButton = new TaskBarMenuButton("");
    _startButton->setObjectName("StartButton");
    _startButton->setIcon(QIcon(":/icons/start.png"));
    _startButton->setIconSize(QSize(29, 31));
    _layout->addWidget(_startButton, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    _startMenu = new QMenu();
    exitAction = new QAction("Exit", this);

    _startMenu->addAction(exitAction);

    _startButton->setMenu(_startMenu);
}

void TaskBar::buildClock()
{
    _clockLabel = new QLabel();
    updateClock();

    _clockTimer = new QTimer();
    connect(_clockTimer, SIGNAL(timeout()), this, SLOT(updateClock()));
    _clockTimer->start(500);

    _layout->addWidget(_clockLabel, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
}

void TaskBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void TaskBar::updateClock()
{
    if(_clockMode == StandardTime)
        _clockLabel->setText(QTime::currentTime().toString("h:mm:ss A"));
    else
        _clockLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void TaskBar::addModule(PandemicModuleBase *module)
{
    QAction *action = new QAction(module->title(), this);
    connect(action, SIGNAL(triggered()), _moduleMapper, SLOT(map()));
    _moduleMapper->setMapping(action, module->package());
    _startMenu->insertAction(exitAction, action);
}

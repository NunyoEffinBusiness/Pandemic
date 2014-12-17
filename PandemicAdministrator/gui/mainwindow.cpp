#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _sWidget = new QStackedWidget();
    _taskBar = new TaskBar();
    _windowArea = new WindowArea();
    _cWidget = new QWidget();

    _cLayout = new QGridLayout();
    _cLayout->setContentsMargins(0, 0, 0, 0);
    _cLayout->setSpacing(0);
    _cWidget->setLayout(_cLayout);

    _cLayout->addWidget(_taskBar, 0, 0, 1, 1, Qt::AlignTop);
    _cLayout->addWidget(_windowArea, 1, 0, 1, 1);
    _windowArea->setBackground(QImage(":/images/background01.jpg").copy(QRect(0, 38, 1920, 1080)));

    _sWidget->addWidget(_cWidget);

    setCentralWidget(_sWidget);

    connect(_taskBar->exitAction, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    _windowArea->resize(size());
    QMainWindow::resizeEvent(event);
}

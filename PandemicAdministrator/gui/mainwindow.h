#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QDockWidget>
#include <QGridLayout>
#include <QImage>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QResizeEvent>
#include <QSplitter>
#include <QStackedWidget>
#include <QWidget>
#include "../api/pandemicwindow.h"
#include "../server/connection.h"
#include "../widgets/taskbar.h"
#include "../widgets/windowarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    TaskBar* taskBar(){ return _taskBar; }
    QMdiArea* windowArea(){ return _windowArea; }

private:
    QGridLayout *_cLayout;
    QStackedWidget *_sWidget;
    QWidget *_cWidget;
    TaskBar *_taskBar;
    WindowArea *_windowArea;

protected:
    void resizeEvent(QResizeEvent *event);

signals:

};

#endif // MAINWINDOW_H

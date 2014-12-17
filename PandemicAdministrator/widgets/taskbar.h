#ifndef TASKBAR_H
#define TASKBAR_H

#include <QAction>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QMdiSubWindow>
#include <QMenu>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QSignalMapper>
#include <QStyle>
#include <QStyleOption>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include "taskbarmenubutton.h"
#include "../api/pandemicmodulebase.h"

class TaskBar : public QWidget
{
    Q_OBJECT
public:
    explicit TaskBar(QWidget *parent = 0);

    QAction *browseHacksAction, *exitAction;

private:
    enum ClockMode{ StandardTime = 0, ArmyTime = 1 };

    QGridLayout *_layout;
    QLabel *_clockLabel;
    QTimer *_clockTimer;
    QSignalMapper *_moduleMapper;
    TaskBarMenuButton *_startButton;

    QMenu *_startMenu;

    ClockMode _clockMode;


protected:
    void buildStartButton();
    void buildAppsButton();
    void buildClock();
    void paintEvent(QPaintEvent *event);


signals:

public slots:
    void addModule(PandemicModuleBase *module);
    void setClockMode(int mode){ _clockMode = (mode == 0) ? StandardTime : ArmyTime; }
    void setClockMode(ClockMode mode){ _clockMode = mode; }
    void updateClock();

};

#endif // TASKBAR_H

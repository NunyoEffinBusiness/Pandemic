#include "taskbarmenubutton.h"

TaskBarMenuButton::TaskBarMenuButton(QString title) :
    QPushButton(title)
{
    setObjectName("TaskBarMenuButton");
    setFixedHeight(38);
}

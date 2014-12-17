#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "../../api/pandemicmodule.h"
#include "../../api/pandemicwindow.h"

class ModuleManager : public PandemicModule
{
    Q_OBJECT
public:
    explicit ModuleManager();

private:
    PandemicWindow *_window;

signals:

public slots:
    virtual void run();

};

#endif // MODULEMANAGER_H

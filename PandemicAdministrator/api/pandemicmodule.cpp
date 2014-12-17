#include "pandemicmodule.h"
#include "../core/application.h"

PandemicModule::PandemicModule(QString package, QString title) :
    PandemicModuleBase(package, title)
{
}

ApplicationBase* PandemicModule::application()
{
    return Application::instance();
}

void PandemicModule::showWindow(PandemicWindow *window)
{
    Application::instance()->showWindow(window);
}

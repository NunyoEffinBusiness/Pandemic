#include "modulemanager.h"

ModuleManager::ModuleManager() :
    PandemicModule("org.newspawn.PandemicPlugin.ModuleManager", "Module Manager")
{
    _window = new PandemicWindow(this, new QWidget());
    _window->setWindowTitle("Module Manager");
}

void ModuleManager::run()
{
    showWindow(_window);
}

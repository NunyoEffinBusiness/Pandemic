#include "application.h"
#include "../builtin/connectionbrowser/connectionbrowser.h"
#include "../builtin/consolelog/consolelog.h"
#include "../builtin/modulemanager/modulemanager.h"

Application* app;

Application::Application(int argc, char *argv[]) :
    ApplicationBase(argc, argv)
{
    app = this;
}

bool Application::initialize()
{
    bool result = ApplicationBase::initialize();
    if(result)
    {
        addBuiltinModule(new ConnectionBrowser());
        addBuiltinModule(new ModuleManager());
        addBuiltinModule(new ConsoleLog());
        _moduleLoader = new ModuleLoader();
    }

    return result;
}

Application* Application::instance()
{
    return app;
}

void Application::closeWindowRequest(PandemicWindow *window)
{
    QList<QMdiSubWindow *> windows = _mainWindow->windowArea()->subWindowList();
    if(windows.contains(window))
        _mainWindow->windowArea()->removeSubWindow(window);
}

void Application::showWindow(PandemicWindow *window)
{

    foreach(QMdiSubWindow* subWindow, _mainWindow->windowArea()->subWindowList())
    {
        PandemicWindow *sw = (PandemicWindow *) subWindow;
        qDebug() << sw->widget();
        if(sw == window || sw->package() == window->package())
        {
            sw->show();
            qDebug() << "Window is already open!";
            return;
        }
    }
    _mainWindow->windowArea()->addSubWindow(window)->show();
}

void Application::addModule(PandemicModuleBase *module)
{
    _moduleList.append(module);
}

void Application::addBuiltinModule(PandemicModuleBase *module)
{
    _mainWindow->taskBar()->addModule(module);
    addModule(module);
}

void Application::runModule(QString package)
{
    foreach(PandemicModuleBase *module, _moduleList)
    {
        if(module->package() == package)
        {
            qDebug() << "Running" << module->package();
            module->run();
            return;
        }
    }
}

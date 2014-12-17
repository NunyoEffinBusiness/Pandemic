#include "applicationbase.h"

ApplicationBase::ApplicationBase(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    QFile f(":/styles/stylesheet.css");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    setStyleSheet(QString(f.readAll().data()));
    f.close();

    setFont(QFont("Open Sans"));

    _log = new OutputLog();

}

bool ApplicationBase::initialize()
{
    _mainWindow = new MainWindow();
    _server = new Server();

    _mainWindow->showFullScreen();

    return true;
}

void ApplicationBase::openConnection(Connection *connection)
{

}

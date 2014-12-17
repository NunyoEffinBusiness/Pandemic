#include "application.h"

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv)
{
}

bool Application::initialize()
{
    _server = new Server();
    _server->setHost("10.0.0.18", (quint16)4456);
    _server->start();
    return true;
}

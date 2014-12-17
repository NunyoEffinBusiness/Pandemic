#include "connectionbrowser.h"

ConnectionBrowser::ConnectionBrowser() :
    PandemicModule("org.newspawn.connbrowser", "Established Connections")
{
    _connList = new ConnectionListWidget();
    _window = new PandemicWindow(this, _connList);
    _window->setWindowTitle("Established Connections");
    _window->setMinimumWidth(400);
}

void ConnectionBrowser::run()
{
    showWindow(_window);
}

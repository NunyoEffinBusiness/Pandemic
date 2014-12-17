#ifndef CONNECTIONBROWSER_H
#define CONNECTIONBROWSER_H

#include "../../api/pandemicmodule.h"
#include "../../api/pandemicwindow.h"
#include "connectionlistwidget.h"

class ConnectionBrowser : public PandemicModule
{
    Q_OBJECT
public:
    explicit ConnectionBrowser();

private:
    ConnectionListWidget *_connList;
    PandemicWindow *_window;

signals:

public slots:
    virtual void run();

};

#endif // CONNECTIONBROWSER_H

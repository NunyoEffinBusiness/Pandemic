#ifndef PANDEMICMODULE_H
#define PANDEMICMODULE_H

#include "../core/applicationbase.h"
#include "pandemicmodulebase.h"
#include "pandemicwindow.h"

class PandemicModule : public PandemicModuleBase
{
    Q_OBJECT
public:
    explicit PandemicModule(QString package, QString title);

    ApplicationBase* application();

private:

signals:

public slots:
    void showWindow(PandemicWindow *window);

};

#endif // PANDEMICMODULE_H

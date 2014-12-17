#ifndef APPLICATION_H
#define APPLICATION_H

#include <QDebug>
#include "applicationbase.h"
#include "../api/pandemicmodulebase.h"
#include "../api/pandemicwindow.h"
#include "moduleloader.h"


class Application : public ApplicationBase
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);

    static Application* instance();
    bool initialize();

    void addBuiltinModule(PandemicModuleBase *module);
    void closeWindowRequest(PandemicWindow *window);

private:

protected:
    QList<PandemicModuleBase *> _moduleList;
    ModuleLoader *_moduleLoader;

signals:

public slots:
    void addModule(PandemicModuleBase *module);
    void runModule(QString package);
    void showWindow(PandemicWindow *window);

};

#endif // APPLICATION_H

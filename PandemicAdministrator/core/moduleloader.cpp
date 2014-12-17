#include "moduleloader.h"

ModuleLoader::ModuleLoader(QObject *parent) :
    QObject(parent)
{

}

QStringList ModuleLoader::scanDirectory()
{
    qDebug() << "Loading Modules!";
    QDir dir("plugins");
    if(!dir.exists())
        QDir().mkpath("plugins");

    QStringList dlls;

    foreach(QString file, dir.entryList())
    {
        if(file.endsWith(".dll"))
        {
            dlls.append(file);
        }
    }

    return dlls;
}

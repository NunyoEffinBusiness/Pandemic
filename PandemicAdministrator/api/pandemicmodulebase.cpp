#include "pandemicmodulebase.h"

PandemicModuleBase::PandemicModuleBase(QString package, QString title) :
    QObject(), _title(title), _package(package.toLower())
{
    _winId = 0;
}

const QString PandemicModuleBase::generateWindowPackage()
{
    const QString name(_package + ".Window" + QString::number(_winId++));
    qDebug() << name;
    return name;
}

void PandemicModuleBase::run()
{

}

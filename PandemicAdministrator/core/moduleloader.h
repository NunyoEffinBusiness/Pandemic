#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QPluginLoader>
#include <QStringList>

class ModuleLoader : public QObject
{
    Q_OBJECT
public:
    explicit ModuleLoader(QObject *parent = 0);

signals:

public slots:
    QStringList scanDirectory();

};

#endif // MODULELOADER_H

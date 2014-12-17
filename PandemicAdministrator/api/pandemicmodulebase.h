#ifndef PANDEMICMODULEBASE_H
#define PANDEMICMODULEBASE_H

#include <QDebug>
#include <QObject>

class PandemicModuleBase : public QObject
{
    Q_OBJECT
public:
    explicit PandemicModuleBase(QString package, QString title);

    const QString title(){ return _title; }
    const QString package(){ return _package; }
    const QString generateWindowPackage();

private:
    const QString _title;
    const QString _package;

    int _winId = 0;

signals:

public slots:
    virtual void run();

};

#endif // PANDEMICMODULEBASE_H

#ifndef OUTPUTLOG_H
#define OUTPUTLOG_H

#include <QMessageLogContext>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QtDebug>

class OutputLog : public QObject
{
    Q_OBJECT
public:
    explicit OutputLog(QObject *parent = 0);
    static void outputDebugMessage(QtMsgType, const QMessageLogContext &, const QString &);
    static OutputLog* instance();

protected:
    QStringList _output;

signals:
    void outputted(QString);
    void outputted(QStringList);

public slots:
    void log(QtMsgType messageType, const QString message);

};

#endif // OUTPUTLOG_H

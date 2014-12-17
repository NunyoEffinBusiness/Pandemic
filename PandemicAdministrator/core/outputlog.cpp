#include "outputlog.h"

OutputLog *outputLog = 0;

OutputLog::OutputLog(QObject *parent) :
    QObject(parent)
{
    outputLog = this;
    qInstallMessageHandler(OutputLog::outputDebugMessage);
}

OutputLog* OutputLog::instance()
{
    return outputLog;
}

void OutputLog::log(QtMsgType messageType, const QString message)
{
    QString m = QString(message).replace("<", "&lt;").replace(">", "&gt;");
    switch(messageType)
    {
        case QtDebugMsg:
            _output << "<text style=\"color:#fff;\">&gt;&gt;&gt;&nbsp;" + m + "</text>";
            emit outputted(_output.last());
            emit outputted(_output);
            break;
        case QtWarningMsg:
            _output << "<text style=\"color:#ff8200;\">&gt;&gt;&gt;&nbsp;" + m + "</text>";
            emit outputted(_output.last());
            emit outputted(_output);
            break;
        case QtCriticalMsg:
            _output << "<text style=\"color:#ff0000;\">&gt;&gt;&gt;&nbsp;" + m + "</text>";
            emit outputted(_output.last());
            emit outputted(_output);
            break;
        case QtFatalMsg:
            _output << "<text style=\"color:#ff0000;\">&gt;&gt;&gt;&nbsp;" + m + "</text>";
            emit outputted(_output.last());
            emit outputted(_output);
            abort();
    }
}

void OutputLog::outputDebugMessage(QtMsgType messageType, const QMessageLogContext &logContext, const QString &message)
{
    Q_UNUSED(logContext);
    OutputLog::instance()->log(messageType, message);
}

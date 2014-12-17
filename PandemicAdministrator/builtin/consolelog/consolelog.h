#ifndef CONSOLELOG_H
#define CONSOLELOG_H

#include "../../api/pandemicmodule.h"
#include "../../api/pandemicwindow.h"
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QSlider>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>

class ConsoleLog : public PandemicModule
{
    Q_OBJECT
public:
    explicit ConsoleLog();

private:
    QPlainTextEdit *_log;
    PandemicWindow *_window;

    int _logLength;

signals:

public slots:
    virtual void run();
    void appendToLog(QString message);

};

#endif // CONSOLELOG_H

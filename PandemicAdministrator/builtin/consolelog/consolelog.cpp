#include "consolelog.h"

ConsoleLog::ConsoleLog() :
    PandemicModule("org.newspawn.PandemicPlugin.ConsoleLog", "Console Log")
{
    _logLength = 80;
    _log = new QPlainTextEdit();
    _log->setObjectName("Console");
    _log->setReadOnly(true);
    connect(application()->outputLog(), SIGNAL(outputted(QString)), this, SLOT(appendToLog(QString)));

    _window = new PandemicWindow(this, _log);
    _window->setWindowTitle("Console Log");
    _window->setMinimumSize(690, 150);
    _window->resize(690, 350);
}

void ConsoleLog::run()
{
    showWindow(_window);
}

void ConsoleLog::appendToLog(QString message)
{
    bool scrollToBottom = false;

    if(_log->verticalScrollBar()->value() == _log->verticalScrollBar()->maximum())
    {
        scrollToBottom = true;
    }

    QTextBlockFormat format;
    format.setLineHeight(30, 0);

    QTextCursor cursor = _log->textCursor();
    cursor.setBlockFormat(format);
    int pos = cursor.position();
    cursor.setPosition(_log->toPlainText().length());
    cursor.insertHtml(message + "<br/><br/><br/>");
    cursor.setPosition(pos);

    if(scrollToBottom) _log->verticalScrollBar()->setValue(_log->verticalScrollBar()->maximum());
}

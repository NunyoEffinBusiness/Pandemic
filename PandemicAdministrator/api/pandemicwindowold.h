#ifndef PANDEMICWINDOW_H
#define PANDEMICWINDOW_H

#include <QDebug>
#include <QCloseEvent>
#include <QColor>
#include <QGridLayout>
#include <QMdiSubWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QResizeEvent>
#include <QWidget>
#include "pandemicmodulebase.h"
#include "../widgets/subwindowtitlebar.h"

class PandemicWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit PandemicWindow(PandemicModuleBase *module, QString name, QWidget *widget = 0);

    const QString package(){ return _package; }
    void setWidget(QWidget *widget);

private:
    const PandemicModuleBase* _module;
    const QString _package;
    QGridLayout *_layout, *_cLayout, *_pLayout;
    QWidget *_widget, *_cWidget, *_pWidget;
    SubWindowTitleBar *_titleBar;

    bool _initialized;

protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


signals:

public slots:
    void setPadding(int left, int top, int right, int bottom){ _pLayout->setContentsMargins(left, top, right, bottom); }

};

#endif // PANDEMICWINDOW_H

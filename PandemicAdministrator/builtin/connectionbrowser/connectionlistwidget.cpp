#include "connectionlistwidget.h"
#include "../../core/application.h"

ConnectionListWidget::ConnectionListWidget() :
    QTableWidget()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setColumnCount(2);
    setRowCount(0);

    setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    setHorizontalHeaderItem(1, new QTableWidgetItem("IP Address"));
    verticalHeader()->setVisible(false);

    setSortingEnabled(true);

    setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(Application::instance()->server(), SIGNAL(connectionListUpdated(QList<Connection*>)), this, SLOT(updateConnectionList(QList<Connection*>)));
    //connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(openConnection(QTableWidgetItem*)));
}

void ConnectionListWidget::updateConnectionList(QList<Connection *> connList)
{
    Connection *conn;
    int i;
    for(i = 0; i < rowCount(); i++)
    {
        if(!connList.contains(((ConnectionItem*)itemAt(i, 0))->connection()))
        {
            removeRow(i);
            _connList.removeAt(i);
            i--;
        }
    }
    foreach(conn, connList)
    {
        if(!_connList.contains(conn))
        {
            setRowCount(rowCount() + 1);
            setItem(rowCount() - 1, 0, new ConnectionItem(0, conn));
            setItem(rowCount() - 1, 1, new ConnectionItem(1, conn));
            _connList.append(conn);
        }
    }
}

void ConnectionListWidget::openConnection(QTableWidgetItem *item)
{
    Application::instance()->openConnection(((ConnectionItem*) item)->connection());
}

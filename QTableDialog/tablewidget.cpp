#include "tablewidget.h"
//#include "adddialog.h"
#include <QHeaderView>
#include <QPushButton>

TableWidget::TableWidget(QDialog *parent)
    : QTabWidget(parent)
{
    table = new TableModel();
    this->setupTab(parent);
    //parent->setLayout()

    //this->setCurrentWidget(this);

}

void TableWidget::setupTab(QDialog *mainwindow)
{


    //widget=new QTabWidget(this) ;
    mainlayout = new QHBoxLayout();

    tableView = new QTableView();

    //tableView->setModel(table);
//排序
    QSortFilterProxyModel *proxy=new QSortFilterProxyModel(tableView);
    proxy->setSourceModel(table);
    tableView->setModel(proxy);
    tableView->setSortingEnabled(true);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    const int Width=80;
    tableView->setColumnWidth(0, Width);
    tableView->setColumnWidth(1, Width);
    tableView->setColumnWidth(2, Width);
    tableView->setColumnWidth(3, Width);
    tableView->setColumnWidth(4, Width);
    tableView->setColumnWidth(5, Width);
    tableView->setColumnWidth(6, Width);
    mainlayout->addWidget(tableView);
   //mainwindow->setLayout(mainlayout);
    this->setLayout(mainlayout);

   // mainwindow->setCentralWidget(widget);

    /*QHBoxLayout *main =new QHBoxLayout;
    mainwindow->setLayout(main);
    main->addWidget(widget);*/

//

        m_pActionCopy = new QAction(tr("复制"), tableView);
        connect(m_pActionCopy, &QAction::triggered, this, &TableWidget::copyData);
        tableView->setSelectionMode(QAbstractItemView::ContiguousSelection); //设置为连续选择模式
        tableView->setContextMenuPolicy(Qt::ActionsContextMenu);             //设置为action菜单模式
        tableView->addAction(this->m_pActionCopy);

}

void TableWidget::showAddEntryDialog()
{
    /*adddialog aDialog;

    if (aDialog.exec()) {
        QString start = aDialog.startText->text();
        QString end = aDialog.endText->text();
        QString FWHM = aDialog.fhwmText->text();
        QString netArea = aDialog.netAreaText->text();
        QString grossArea = aDialog.grossAreaText->text();
        QString centroid = aDialog.centroidText->text();
        QString uncertainty = aDialog.uncertaintyText->text();


        addEntry(start, end, FWHM, netArea, grossArea,centroid,uncertainty);
    }*/

}

void TableWidget::addEntry(QString start, QString end, QString fhwm, QString netArea, QString grossArea, QString centroid, QString uncertainty)
{
    QList<ModelItem>  list = table->getList();


        //if (!list.contains(pair)) {
            table->insertRows(0, 1, QModelIndex());

            QModelIndex index = table->index(0, 0, QModelIndex());
            table->setData(index, start.toDouble(), Qt::EditRole);
            index = table->index(0, 1, QModelIndex());
            table->setData(index, end.toDouble(), Qt::EditRole);
            index = table->index(0, 2, QModelIndex());
            table->setData(index, fhwm.toDouble(), Qt::EditRole);
            index = table->index(0, 3, QModelIndex());
            table->setData(index, netArea.toInt(), Qt::EditRole);
            index = table->index(0, 4, QModelIndex());
            table->setData(index, grossArea.toInt(), Qt::EditRole);
            index = table->index(0, 5, QModelIndex());
            table->setData(index, centroid.toDouble(), Qt::EditRole);
            index = table->index(0, 6, QModelIndex());
            table->setData(index, uncertainty.toDouble(), Qt::EditRole);
            //removeTab(indexOf(newAddressTab));
        /*} else {
            QMessageBox::information(this, tr("Duplicate Name"),
                tr("The start \"%1\" already exists.").arg(start));
        }*/


}

void TableWidget::copyData()
{
    tableView->selectAll();//
    QModelIndexList indexes = tableView->selectionModel()->selectedIndexes();

    if (indexes.count() == 0)
    {
        //select nothing
        return;
    }

    QMap<QString, QString> map;
    QModelIndex index;
    int k = 0;
    int maxCol = 0;
    int maxRow = 0;
    int minCol = 0;
    int minRow = 0;

    foreach (index, indexes)
    {
        int col = index.column();
        int row = index.row();
        if (k == 0)
        {
            minCol = col;
            minRow = row;
        }

        if (col > maxCol)
            maxCol = col;

        if (row > maxRow)
            maxRow = row;

        QString text = index.model()->data(index, Qt::DisplayRole).toString();

        map[QString::number(row) + "," + QString::number(col)] = text;
        k++;
    }



    QString rs = "";
    for (int col=0;col<index.model()->columnCount(index);col++)
    {
        rs+=index.model()->headerData(col,Qt::Horizontal).toString()+"\t";
    }
    rs+="\n";
    for (int row = minRow; row <= maxRow; row++)
    {
        for (int col = minCol; col <= maxCol; col++)
        {
            if (col != minCol)
                rs += "\t";

            rs += map[QString::number(row) + "," + QString::number(col)];
        }
        rs+="\n";
    }

    rs += "\r\n";
    //复制到剪贴板
    QClipboard *board = QApplication::clipboard();
    board->setText(rs);
}

void TableWidget::copyData2()
{
    QStringList list;
    QModelIndexList indexes = tableView->selectionModel()->selectedIndexes();
    if (indexes.count() == 0)
    {
        //select nothing
        return;
    }

    foreach (const QModelIndex &index, indexes)
    {
        list << index.data().toString();
    }

    QApplication::clipboard()->setText(list.join("\t"));
}

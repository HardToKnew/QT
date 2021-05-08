#include "tablewidget.h"
#include <QHeaderView>
#include <QPushButton>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <iostream>
using namespace std;

TableWidget::TableWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    this->setupTab();

}

void TableWidget::setupTab()
{

    mainlayout = new QHBoxLayout(this);
    this->setLayout(mainlayout);
    tableView = new QTableView(this);


    QSortFilterProxyModel *proxy=new QSortFilterProxyModel(tableView);
    proxy->setSourceModel(table);
    tableView->setModel(proxy);
    tableView->setSortingEnabled(true);//排序
    tableView->sortByColumn(0, Qt::AscendingOrder);//升序

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行
    const int Width=80;
    tableView->setColumnWidth(0, Width);
    tableView->setColumnWidth(1, Width);
    tableView->setColumnWidth(2, Width);
    tableView->setColumnWidth(3, Width);
    tableView->setColumnWidth(4, Width);
    tableView->setColumnWidth(5, Width);
    tableView->setColumnWidth(6, Width);
    mainlayout->addWidget(tableView);

    m_pActionCopy = new QAction(tr("复制"), tableView);
    connect(m_pActionCopy, &QAction::triggered, this, &TableWidget::copyData);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection); //设置为连续选择模式
    tableView->setContextMenuPolicy(Qt::ActionsContextMenu);             //设置为action菜单模式
    tableView->addAction(this->m_pActionCopy);

    QAction *ActionPrint = new QAction(tr("打印"), tableView);
    connect(ActionPrint, &QAction::triggered, this, &TableWidget::printAction);
    tableView->addAction(ActionPrint);

}

void TableWidget::showAddEntryDialog()
{


}

void TableWidget::addEntry(QString start, QString end, QString fhwm, QString netArea, QString grossArea, QString centroid, QString uncertainty)
{
    QList<ModelItem>  list = table->getList();

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



}
void TableWidget::removeEntry(int row)
{
    table->removeRows(row, 1, QModelIndex());
}

void TableWidget::copyData()
{
    tableView->selectAll();//
    QModelIndexList indexes = tableView->selectionModel()->selectedIndexes();


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

void TableWidget::printAction()
{



    QPrinter printer;
    QPrintDialog *Dialog = new QPrintDialog (&printer);
    if (Dialog->exec()){
        QPainter *painter = new QPainter();
        if(painter->begin(&printer))
        {
            painter->setRenderHint(QPainter::Antialiasing, true);
               // 设置画笔颜色、宽度
            painter->setPen(QPen(QColor(255, 255, 255), 2));
               // 设置画刷颜色
            painter->setBrush(QColor(255, 255, 255));
            QRect rect(0,0,800,600);
               //整张图设置画刷白底
            painter->fillRect(rect,QColor(255, 255, 255));
            painter->drawRect(rect);
               //画数据部分的线条
            painter->setPen(QPen(QColor(0, 0, 0)));

            QFont font;
            font.setPointSize(12);
            font.setFamily("黑体");
            font.setItalic(true);
            painter->setFont(font);

            tableView->selectAll();
            QModelIndexList indexes = tableView->selectionModel()->selectedIndexes();
            QString rs = "";
            QModelIndex index;

            QMap<QString, QString> map;
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

            for (int row = 0,i=0,page=1; row <= maxRow;i++, row++)
            {

                if(i==0)
                    printPages(painter,page);
                for (int col = 0; col <=maxCol; col++)
                {
                    painter->setFont(font);
                    painter->drawText(80+100*col,130+40*i,100,50,Qt::AlignVCenter,map[QString::number(row) + "," + QString::number(col)]+"\t");
                }
                if(150+50*i>1120){
                    i=0;
                    printer.newPage();
                    printPages(painter,++page);
                }
            }
            painter->end();
        }
    }
}


void TableWidget::printPages(QPainter *painter,int page)
{
    QMap<QString, QString> header;
    QModelIndex index;
    QFont font;
    font.setPointSize(10);
    font.setFamily("黑体");
    font.setItalic(true);
    painter->setFont(font);
    for (int col=0;col<table->columnCount(index);col++)
    {
        QString text=table->headerData(col,Qt::Horizontal,Qt::DisplayRole).toString();
        header[QString::number(0) + "," + QString::number(col)] = text;
        painter->drawText(10+col*100,110,100,50,Qt::AlignRight,text);
    }
    painter->drawText(360,1060,100,50,Qt::AlignVCenter,"第"+QString::number(page)+"页");

    QFont fontTitle;
    fontTitle.setPointSize(16);
    fontTitle.setFamily("黑体");
    fontTitle.setItalic(true);
    painter->setFont(fontTitle);
    painter->drawText(250,30,500,30,Qt::AlignVCenter,"Regions of Interest Details");
    QVector<QLine> lines;
    lines.append(QLine(QPoint(50,90),QPoint(740,90)));//上边
    lines.append(QLine(QPoint(50,1050),QPoint(740,1050)));//1
    lines.append(QLine(QPoint(50,90),QPoint(50,1050)));//1
    lines.append(QLine(QPoint(740,90),QPoint(740,1050)));//1

    lines.append(QLine(QPoint(50,130),QPoint(740,130)));
    painter->drawLines(lines);

}


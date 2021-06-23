#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::fillData()
{
    QList<QString> list1 = {
        QString("Lisa"),
        QString("Liso4ka"),
        QString("Lison"),
        QString("Lisaveta"),
        QString("Lisssa"),
        QString("Lisochka"),
        QString("Lis"),
    };

    QList<QString> list2 = {
        QString("NeLisa"),
        QString("NeLiso4ka"),
        QString("NeLison"),
        QString("NeLisaveta"),
        QString("NeLisssa"),
        QString("NeLisochka"),
        QString("NeLis"),
    };

    for (int i=0; i<list1.size();i++) {
        ui->listWidget->addItem(list1.value(i));
    }
    for (int i=0; i<list2.size();i++) {
        ui->listWidget_2->addItem(list2.value(i));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillData();

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->viewport()->setAcceptDrops(true);
    ui->listWidget->setDropIndicatorShown(true);
    ui->listWidget->setDefaultDropAction(Qt::MoveAction);

    ui->listWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listWidget_2->setDragEnabled(true);
    ui->listWidget_2->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget_2->viewport()->setAcceptDrops(true);
    ui->listWidget_2->setDropIndicatorShown(true);
    ui->listWidget_2->setDefaultDropAction(Qt::MoveAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

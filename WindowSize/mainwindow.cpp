#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QSize windowSize = event->size();
    ui->SizeLabel->setText(QString::number(windowSize.width()) + " X " + QString::number(windowSize.height()));
    QMainWindow::resizeEvent(event);
}

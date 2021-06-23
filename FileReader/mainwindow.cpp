#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFile(){
    QFileDialog dialog(this);

    dialog.setNameFilter(tr("Text files (*.txt)"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList filePath;
    if (dialog.exec()){
        filePath = dialog.selectedFiles();
        return filePath.last();
    }

    return "";
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(getFile());
}

void MainWindow::on_pushButton2_clicked()
{
    ui->label_2->setText(getFile());
}

void MainWindow::on_pushButton3_clicked()
{
    QFile inputFile(ui->label->text());
    QFile outputFile(ui->label_2->text());

    if (!inputFile.exists() || !outputFile.exists()){
        QMessageBox::information(this, tr("Error"), tr("File not chosen"));
        return;
    }


    if (inputFile.open(QIODevice::ReadOnly) && outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream in(&inputFile);
        QTextStream out(&outputFile);

        while (!in.atEnd())
        {
            QString line = in.read(1);
            if (QString::compare(line, "\t", Qt::CaseInsensitive) == 0){
                out << " ";
            } else if (QString::compare(line, "\n", Qt::CaseInsensitive) != 0 && QString::compare(line, "\r", Qt::CaseInsensitive) != 0){
                out << line;
            }
        }

        inputFile.close();
        outputFile.close();
    }

    QMessageBox::information(this, tr("Success"), tr("Done"));
}

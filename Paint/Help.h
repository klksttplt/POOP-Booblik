#ifndef HELP_H
#define HELP_H

#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QLineEdit>
#include <QProgressDialog>
#include <QTextBrowser>
#include <QColorDialog>
#include <QInputDialog>

class Help : public QWidget {
    Q_OBJECT

public:
    Help(const QString& strPath,
                const QString& strFileName,
                      QWidget* pwgt       = 0
               ) : QWidget(pwgt)
    {

        QTextBrowser* ptxtBrowser = new QTextBrowser;



        ptxtBrowser->setSearchPaths(QStringList() << strPath);
        ptxtBrowser->setSource(QString(strFileName));


        QVBoxLayout* pvbxLayout = new QVBoxLayout;
        QHBoxLayout* phbxLayout = new QHBoxLayout;

        pvbxLayout->addLayout(phbxLayout);
        pvbxLayout->addWidget(ptxtBrowser);
        setLayout(pvbxLayout);
        this->setWindowTitle("Help");
    }
};

#endif // HELP_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "Paint.h"
#include "Help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveAs();

    void getHelp();

private:
    void setActions();
    void setMenus();
    void createToolBars();

    Paint* scene;
    QGraphicsView* view;

    QMenu *fileMenu;
    QMenu *quickMenu;
    QMenu *helpMenu;
    QToolBar *quickAcessToolBar;

    QAction *saveAction;
    QAction *exitAction;

    QAction *biggerAction;
    QAction *smallerAction;

    QAction *eraseAction;

    QAction *lineAction;
    QAction *circleAction;
    QAction *rectAction;
    QAction *trianAction;

    QAction *redAction;
    QAction *blueAction;
    QAction *blackAction;
    QAction *greenAction;
    QAction *pinkAction;
    QAction *yellowAction;

    QAction *helpAction;

    Help *help = new Help(":/resources/html", "index.html");
};
#endif // MAINWINDOW_H

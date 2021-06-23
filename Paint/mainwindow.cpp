#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), scene(new Paint(0,0,600, 600)), view(new QGraphicsView){

    scene->currentPaintModes = Paint::paintModes::def;

    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing
                         | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);

    setActions();
    setMenus();
    createToolBars();

    this->setWindowTitle(tr("pAiNt"));
}

MainWindow::~MainWindow(){
    delete scene;
    delete view;
    delete fileMenu;
    delete quickMenu;
    delete helpMenu;
    delete quickAcessToolBar;
    delete saveAction;
    delete exitAction;
    delete eraseAction;
    delete trianAction;
    delete lineAction;
    delete circleAction;
    delete rectAction;
    delete redAction;
    delete blueAction;
    delete blackAction;
    delete greenAction;
    delete pinkAction;
    delete yellowAction;
    delete biggerAction;
    delete smallerAction;
    delete helpAction;
    delete help;
}

void MainWindow::setActions(){

    this->saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setIcon(QIcon(":/resources/icons/save.png"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    this->exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setIcon(QIcon(":/resources/icons/exit.png"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    this->eraseAction = new QAction(tr("Erase"), this);
    eraseAction->setIcon(QIcon(":/resources/icons/exit.png"));
    connect(eraseAction, SIGNAL(triggered()), scene, SLOT(erase()));

    lineAction = new QAction(tr("Line"), this);
    lineAction->setIcon(QIcon(":/resources/icons/addLine.png"));
    connect(lineAction, SIGNAL(triggered()), scene, SLOT(addLine()));

    circleAction = new QAction(tr("Circle"), this);
    circleAction->setIcon(QIcon(":/resources/icons/addCircle.png"));
    connect(circleAction, SIGNAL(triggered()), scene, SLOT(addCircle()));

    trianAction = new QAction(tr("Triangle"), this);
    trianAction->setIcon(QIcon(":/resources/icons/addTriangle.png"));
    connect(trianAction, SIGNAL(triggered()), scene, SLOT(addTrian()));

    rectAction = new QAction(tr("Rectangle"), this);
    rectAction->setIcon(QIcon(":/resources/icons/addRect.png"));
    connect(rectAction, SIGNAL(triggered()), scene, SLOT(addRect()));

    redAction = new QAction(tr("Red"), this);
    redAction->setIcon(QIcon(":/resources/icons/red.png"));
    connect(redAction, SIGNAL(triggered()), scene, SLOT(setRedBrush()));

    blueAction = new QAction(tr("Blue"), this);
    blueAction->setIcon(QIcon(":/resources/icons/blue.png"));
    connect(blueAction, SIGNAL(triggered()), scene, SLOT(setBlueBrush()));

    blackAction = new QAction(tr("Black"), this);
    blackAction->setIcon(QIcon(":/resources/icons/black.png"));
    connect(blackAction, SIGNAL(triggered()), scene, SLOT(setBlackBrush()));

    greenAction = new QAction(tr("Green"), this);
    greenAction->setIcon(QIcon(":/resources/icons/green.png"));
    connect(greenAction, SIGNAL(triggered()), scene, SLOT(setGreenBrush()));

    pinkAction = new QAction(tr("Pink"), this);
    pinkAction->setIcon(QIcon(":/resources/icons/pink.png"));
    connect(pinkAction, SIGNAL(triggered()), scene, SLOT(setPinkBrush()));

    yellowAction = new QAction(tr("Yellow"), this);
    yellowAction->setIcon(QIcon(":/resources/icons/yellow.png"));
    connect(yellowAction, SIGNAL(triggered()), scene, SLOT(setYellowBrush()));

    biggerAction = new QAction(tr("Bigger"), this);
    biggerAction->setIcon(QIcon(":/resources/icons/plus.png"));
    connect(biggerAction, SIGNAL(triggered()), scene, SLOT(biggerPen()));

    smallerAction = new QAction(tr("Smaller"), this);
    smallerAction->setIcon(QIcon(":/resources/icons/minus.png"));
    connect(smallerAction, SIGNAL(triggered()), scene, SLOT(smallerPen()));

    helpAction = new QAction(tr("Help"), this);
    helpAction->setShortcut(tr("Ctrl+H"));
    helpAction->setIcon(QIcon(":/resources/icons/help.png"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(getHelp()));

}

void MainWindow::setMenus(){
    fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    quickMenu = this->menuBar()->addMenu(tr("Quick Actions"));
    quickMenu->addAction(eraseAction);
    quickMenu->addAction(lineAction);
    quickMenu->addAction(blueAction);

    helpMenu = this->menuBar()->addMenu("Help");
    helpMenu->addAction(helpAction);
}

void MainWindow::createToolBars(){
    quickAcessToolBar = addToolBar(tr("Quick Access Menu"));
    quickAcessToolBar->addAction(saveAction);
    quickAcessToolBar->addSeparator();
    quickAcessToolBar->addAction(eraseAction);
    quickAcessToolBar->addAction(lineAction);
    quickAcessToolBar->addAction(circleAction);
    quickAcessToolBar->addAction(rectAction);
    quickAcessToolBar->addAction(trianAction);

    quickAcessToolBar->addSeparator();
    quickAcessToolBar->addAction(biggerAction);
    quickAcessToolBar->addAction(smallerAction);

    quickAcessToolBar->addSeparator();
    quickAcessToolBar->addAction(blackAction);
    quickAcessToolBar->addAction(redAction);
    quickAcessToolBar->addAction(yellowAction);
    quickAcessToolBar->addAction(greenAction);
    quickAcessToolBar->addAction(blueAction);
    quickAcessToolBar->addAction(pinkAction);




}

void MainWindow::saveAs(){
    QString outName = QFileDialog::getSaveFileName(this, "Output file", tr("C:/Users/User/new image"), "Image (*.png)");
    QPixmap pixmap = view->grab();
    pixmap.save(outName);
}

void MainWindow::getHelp(){
    help->resize(400, 300);
    help->show();
}





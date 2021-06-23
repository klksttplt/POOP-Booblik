#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QBrush>

class Paint: public QGraphicsScene{
    Q_OBJECT
public:
    Paint(qreal x, qreal y, qreal width, qreal height):
        QGraphicsScene(x,y,width, height), brush(Qt::black),
        pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
        currentItem(nullptr){}

    enum class paintModes {def, lineState, rectState, circleState, trianState};

    paintModes currentPaintModes;
    QBrush brush;
    QPen pen;

    void mousePressEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;

private:
    QGraphicsItem* currentItem;
    QList<QGraphicsItem *> selectedItems;

public slots:
    void addLine();
    void addCircle();
    void addRect();
    void addTrian();

    void biggerPen();
    void smallerPen();

    void erase();
    void setRedBrush(){brush.setColor(Qt::red);};
    void setPinkBrush(){brush.setColor(Qt::magenta);};
    void setBlueBrush(){brush.setColor(Qt::blue);};
    void setYellowBrush(){brush.setColor(Qt::yellow);};
    void setBlackBrush(){brush.setColor(Qt::black);};
    void setGreenBrush(){brush.setColor(Qt::green);};


};


#endif

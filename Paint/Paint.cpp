#include "Paint.h"
#include <algorithm>

using std::min;
using std::max;

void Paint::mousePressEvent(QGraphicsSceneMouseEvent *_){
    if(currentItem or currentItem!=nullptr){
        delete currentItem;
    }
}

void Paint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
    switch(currentPaintModes){
    case paintModes::def:
        event->ignore();
        break;
    case paintModes::lineState:{
        delete currentItem;
        auto line = new QGraphicsLineItem(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().rx(), event->scenePos().ry());
        line->setPen(pen);
        this->addItem(line);
        currentItem = line;
        break;
    }
    case paintModes::rectState:{
        delete currentItem;
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto rect = new QGraphicsRectItem(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        rect->setBrush(brush);
        rect->setPen(pen);
        this->addItem(rect);
        currentItem = rect;
        break;
    }
    case paintModes::circleState:{
        delete currentItem;
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto circ = new QGraphicsEllipseItem(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        circ->setBrush(brush);
        circ->setPen(pen);
        this->addItem(circ);
        currentItem = circ;
        break;
    }
    case paintModes::trianState:{
        delete currentItem;

        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());

        QPolygonF tr;
        tr.append(QPointF(min_x,0));
        tr.append(QPointF(0,min_y));
        tr.append(QPointF(max_x,0));
        tr.append(QPointF(min_x,0));

       auto trian = new QGraphicsPolygonItem(tr);
        trian->setBrush(brush);
         trian->setPen(pen);
        this->addItem(trian);
        currentItem = trian;
        break;
    }
    default:
        break;
    }

}

void Paint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(currentPaintModes==paintModes::lineState || currentPaintModes==paintModes::rectState || currentPaintModes==paintModes::circleState){
        currentItem = nullptr;
    } else if(currentPaintModes==paintModes::def){
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        selectedItems = items(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        for(auto i:selectedItems){
            delete i;
        }
        selectedItems = QList<QGraphicsItem*>();
    }
}

void Paint::erase() Q_SLOT{
    this->currentPaintModes = paintModes::def;
}

void Paint::addLine() Q_SLOT{
    this->currentPaintModes = paintModes::lineState;
}

void Paint::addCircle() Q_SLOT{
    this->currentPaintModes = paintModes::circleState;
}

void Paint::addRect() Q_SLOT{
    this->currentPaintModes = paintModes::rectState;
}

void Paint::addTrian() Q_SLOT{
    this->currentPaintModes = paintModes::trianState;
}


void Paint::biggerPen(){
    pen.setWidth(pen.width()+2);
}

void Paint::smallerPen(){
    if(pen.width()){
        pen.setWidth(pen.width()-2);
    }
}

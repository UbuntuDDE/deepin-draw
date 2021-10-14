/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     WangXin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "cgraphicstriangleitem.h"
#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"

#include <QPainter>

#include <QDebug>
#include <QtMath>

CGraphicsTriangleItem::CGraphicsTriangleItem(CGraphicsItem *parent)
    : CGraphicsRectItem (parent)
{

}

CGraphicsTriangleItem::CGraphicsTriangleItem(const QRectF &rect, CGraphicsItem *parent)
    : CGraphicsRectItem (rect, parent)
{

}

CGraphicsTriangleItem::CGraphicsTriangleItem(qreal x, qreal y, qreal w, qreal h, CGraphicsItem *parent)
    : CGraphicsRectItem (x, y, w, h, parent)
{

}

CGraphicsTriangleItem::CGraphicsTriangleItem(const SGraphicsTriangleUnitData *data, const SGraphicsUnitHead &head, CGraphicsItem *parent)
    : CGraphicsRectItem (data->rect, head, parent)
{

}

CGraphicsUnit CGraphicsTriangleItem::getGraphicsUnit() const
{
    CGraphicsUnit unit;

    unit.head.dataType = this->type();
    unit.head.dataLength = sizeof(SGraphicsTriangleUnitData);
    unit.head.pen = this->pen();
    unit.head.brush = this->brush();
    unit.head.pos = this->pos();
    unit.head.rotate = this->rotation();
    unit.head.zValue = this->zValue();

    unit.data.pTriangle = new SGraphicsTriangleUnitData();
    unit.data.pTriangle->rect.topLeft = this->rect().topLeft();
    unit.data.pTriangle->rect.bottomRight = this->rect().bottomRight();

    return  unit;
}


QPainterPath CGraphicsTriangleItem::shape() const
{
    QPainterPath path;
    QRectF rc = rect();

    QPointF top = QPointF((rc.x() + rc.width() / 2), rc.y());

    QPolygonF item;
    item << rc.bottomLeft() << top << rc.bottomRight();
    path.addPolygon(item);
    path.closeSubpath();
    return qt_graphicsItem_shapeFromPath(path, pen());
}

int CGraphicsTriangleItem::type() const
{
    return TriangleType;
}

QRectF CGraphicsTriangleItem::boundingRect() const
{
    return shape().controlPointRect();
}

void CGraphicsTriangleItem::duplicate(CGraphicsItem *item)
{
    CGraphicsRectItem::duplicate(item);
}

QPainterPath CGraphicsTriangleItem::getHighLightPath()
{
    QPainterPath path;
    QRectF rc = rect();

    QPointF top = QPointF((rc.x() + rc.width() / 2), rc.y());

    QPolygonF item;
    item << rc.bottomLeft() << top << rc.bottomRight();
    path.addPolygon(item);
    path.closeSubpath();
    return path;
}


void CGraphicsTriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    updateGeometry();
    QRectF rc = rect();

    QPointF top = QPointF((rc.x() + rc.width() / 2), rc.y());

    //先绘制填充区域
    QPolygonF polyForBrush;
    qreal offsetWidth = pen().widthF() / 2.0;
    QLineF line1(top,rc.bottomLeft());
    QLineF line2(rc.bottomLeft(),rc.bottomRight());
    QLineF line3(rc.bottomRight(),top);
    QVector<QLineF> lines;
    lines<<line3<<line1<<line2;
    for(int i = 0;i<lines.size();++i)
    {
        QLineF ln1  = lines.at(i);
        QLineF ln2  = (i == lines.size() - 1?lines[0]: lines[i+1]);
        qreal angle = 180 - ln1.angleTo(ln2);

        qreal offsetLen = offsetWidth/qSin(qDegreesToRadians(angle/2.0));
        QLineF tempLine(ln2);
        tempLine.setAngle(tempLine.angle()+angle/2.0);
        tempLine.setLength(offsetLen);

        polyForBrush.append(tempLine.p2());
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush());
    painter->drawPolygon(polyForBrush);


    //再绘制描边
    QPolygonF polyForPen;
    polyForPen << rc.bottomLeft() << top << rc.bottomRight();

    painter->setPen(pen().width() == 0 ? Qt::NoPen : pen());
    painter->setBrush(Qt::NoBrush);
    painter->drawPolygon(polyForPen);

    //是否选中的情况
    if (this->getMutiSelect()) {
        painter->setClipping(false);
        QPen pen;
        pen.setWidthF(1 / CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getScale());
        if ( CManageViewSigleton::GetInstance()->getThemeType() == 1) {
            pen.setColor(QColor(224, 224, 224));
        } else {
            pen.setColor(QColor(69, 69, 69));
        }
        painter->setPen(pen);
        painter->setBrush(QBrush(Qt::NoBrush));
        painter->drawRect(this->boundingRect());
        painter->setClipping(true);
    }
}

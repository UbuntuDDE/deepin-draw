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
#ifndef CGRAPHICSPOLYGONITEM_H
#define CGRAPHICSPOLYGONITEM_H

#include "csizehandlerect.h"
#include "cgraphicsrectitem.h"
#include <QtGlobal>
#include <QVector>
#include <QRectF>

class CGraphicsPolygonItem : public CGraphicsRectItem
{
public:
    explicit CGraphicsPolygonItem(int count = 0, CGraphicsItem *parent = nullptr);
    explicit CGraphicsPolygonItem(int count, const QRectF &rect, CGraphicsItem *parent = nullptr);
    explicit CGraphicsPolygonItem(int count, qreal x, qreal y, qreal w, qreal h, CGraphicsItem *parent = nullptr);
    CGraphicsPolygonItem(const SGraphicsPolygonUnitData *data, const SGraphicsUnitHead &head, CGraphicsItem *parent = nullptr);
    virtual QPainterPath shape() const Q_DECL_OVERRIDE;
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual int  type() const Q_DECL_OVERRIDE;
    /**
     * @brief duplicate 拷贝自己
     * @return
     */
    virtual void duplicate(CGraphicsItem *item) Q_DECL_OVERRIDE;
    virtual CGraphicsUnit getGraphicsUnit() const Q_DECL_OVERRIDE;
    void setRect(const QRectF &rect) Q_DECL_OVERRIDE;
    void setPointCount(int num);
    virtual void resizeTo(CSizeHandleRect::EDirection dir, const QPointF &point, bool bShiftPress, bool bAltPress) Q_DECL_OVERRIDE;
    int nPointsCount() const;

    void setListPoints(const QVector<QPointF> &listPoints);
    /**
     * @brief getHighLightPath 获取高亮path
     * @return
     */
    virtual QPainterPath getHighLightPath() Q_DECL_OVERRIDE;


protected:
    virtual void updateShape() Q_DECL_OVERRIDE {calcPoints();}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    void calcPoints();
    static void calcPoints_helper(QVector<QPointF> &outVector, int n, const QRectF& rect,qreal offset = 0.0);

private:
    int m_nPointsCount; //点数
    QVector<QPointF> m_listPointsForBrush;
    QVector<QPointF> m_listPoints;

    friend class CGraphicsPolygonalStarItem;
};

#endif // CGRAPHICSPOLYGONITEM_H

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
#ifndef CSELECTTOOL_H
#define CSELECTTOOL_H
#include "idrawtool.h"
#include "globaldefine.h"
#include "csizehandlerect.h"


#include <QCursor>

class CGraphicsItem;
class CGraphicsRotateAngleItem;
class CGraphicsItemSelectedMgr;
class CGraphicsItemHighLight;
class CGraphicsRectItem;
class GraphicsEllipseItem;
class QUndoCommand;

class CSelectTool : public IDrawTool
{
public:
    CSelectTool();
    virtual ~CSelectTool();
    /**
     * @brief isDragging　是否正在进行拖拽操作
     */
    bool isDragging();
    /**
     * @brief mousePressEvent　鼠标点击事件
     * @param event　场景事件
     * @param scene　场景句柄
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene);
    /**
     * @brief mouseMoveEvent 鼠标移动事件
     * @param event 场景事件
     * @param scene 场景句柄
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene);
    /**
     * @brief mouseReleaseEvent　鼠标弹起事件
     * @param event 场景事件
     * @param scene 场景句柄
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene);
private:
    /**
     * @brief pintToRect　任意两点确定一个矩形
     * @param point1 任意一点
     * @param point2 任意一点
     */
    QRectF pointToRect(QPointF point1, QPointF point2);
    /**
     * @brief getItemByPointToItemMinDistance　获取点到 item 集合中距离最短的item
     * @param mousePoint 鼠标点
     * @param detectItems 待比较的 QGraphicsItem
     */
    QGraphicsItem *getItemByMousePointToItemMinDistance(QPointF mousePoint, QList<QGraphicsItem *> detectItems);
    /**
     * @brief getItemByPointToItemMinDistance　获取点到 item 最短的距离
     * @param mousePoint 鼠标点
     * @param detectItems 待比较的 QGraphicsItem
     */
    double getItemMinDistanceByMousePointToItem(QPointF mousePoint, QGraphicsItem *detectItems);
private:
    QGraphicsItem *m_currentSelectItem;
    QGraphicsItem *m_highlightItem;
    QGraphicsRectItem *m_frameSelectItem;
    CSizeHandleRect::EDirection m_dragHandle; //选中的方块方向
    bool m_bRotateAng;
    qreal m_rotateAng;
    QPointF m_initRotateItemPos;
    CGraphicsRotateAngleItem *m_RotateItem;
    QCursor m_textEditCursor;
    bool m_doCopy;
    bool m_isMulItemMoving;       //当前有多个(超过1个)item正在被拖拽移动(注意和m_isItemMoving的区别)
    bool m_doResize;
    bool m_isItemMoving = false;  //当前有item正在被拖拽移动(注意和m_isMulItemMoving的区别)

};

#endif // CSELECTTOOL_H

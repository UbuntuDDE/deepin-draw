﻿/*
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
#ifndef CGRAPHICSITEM_H
#define CGRAPHICSITEM_H

#include "csizehandlerect.h"
#include "globaldefine.h"
#include "sitemdata.h"
#include "cdrawparamsigleton.h"

#include <QAbstractGraphicsShapeItem>
#include <QCursor>

class CGraphicsItem : public QAbstractGraphicsShapeItem
{
public:
    /**
     * @brief CGraphicsItem 构造函数
     * @param parent 父图元
     */
    CGraphicsItem(QGraphicsItem *parent );

    /**
     * @brief CGraphicsItem 构造函数
     * @param head 图元数据
     * @param parent 父图元
     */
    CGraphicsItem(const SGraphicsUnitHead &head, QGraphicsItem *parent);
    enum {Type = UserType};

    /**
     * @brief type 返回当前图元类型
     * @return
     */
    virtual int  type() const Q_DECL_OVERRIDE;

    /**
     * @brief hitTest 碰撞检测，用来检测鼠标在图元的哪个点位上
     * @param point 鼠标指针
     * @return
     */
    virtual CSizeHandleRect::EDirection  hitTest( const QPointF &point ) const;

    /**
     * @brief resizeTo 沿一个方向拉伸图元
     * @param dir 拉伸方向
     * @param point 移动距离
     */
    virtual void resizeTo(CSizeHandleRect::EDirection dir, const QPointF &point ) = 0;

    /**
     * @brief resizeTo 沿一个方向拉伸图元
     * @param dir 拉伸方向
     * @param point 移动距离
     * @param bShiftPress shift键是否按下
     * @param bAltPress alt键是否按下
     */
    virtual void resizeTo(CSizeHandleRect::EDirection dir, const QPointF &point, bool bShiftPress, bool bAltPress ) = 0;
    /**
     * @brief resizeTo 缩放矩形时，用于设置矩形大小与位置
     * @param dir 8个方向
     * @param offset x，y方向移动距离
     * @param xScale X轴放大缩小比例
     * @param yScale y轴放大缩小比例
     */
    virtual void resizeTo(CSizeHandleRect::EDirection dir, const QPointF &offset, const double &xScale, const double &yScale, bool bShiftPress, bool bAltPress);

    /**
     * @brief duplicate 复制this图元到item图元
     * @param item 复制后的图元
     */
    virtual void duplicate(CGraphicsItem *item);

    /**
     * @brief getGraphicsUnit 获取图元数据
     * @return
     */
    virtual CGraphicsUnit getGraphicsUnit() const;

    /**
     * @brief move  移动图元
     * @param beginPoint 移动起始点
     * @param movePoint 移动终点
     */
    virtual void move(QPointF beginPoint, QPointF movePoint);

    /**
      * @brief updateShape  刷新图元的形状(属性变化时调用重新计算图元的形状和样式)
      */
    virtual void updateShape(){}

    /**
     * @brief setSizeHandleRectFlag 设置边界各个方向上的矩形是否可见
     * @param dir 方向
     * @param flag true: 显示  false:不显示
     */
    void setSizeHandleRectFlag(CSizeHandleRect::EDirection dir, bool flag);

    /**
     * @brief qt_graphicsItem_shapeFromPath 根据画笔属性，把图元形状转为路径   此函数为Qt源码中自带的
     * @param path 形状路径
     * @param pen 画笔
     * @return  转换后的路径
     */
    static QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath &path, const QPen &pen);

    virtual QRectF rect() const = 0;

    /**
     * @brief setMutiSelect 设置图元选中状态
     * @param flag
     */
    void setMutiSelect(bool flag);

    /**
     * @brief getMutiSelect 获取图元选中状态
     * @return
     */
    bool getMutiSelect() const;

    /**
     * @brief getHighLightPath 获取高亮path
     * @return
     */
    virtual QPainterPath getHighLightPath();

protected:
    /**
     * @brief updateGeometry 更新状态矩形位置
     */
    virtual void updateGeometry() = 0;

    /**
     * @brief setState 设置图元外接矩形状态
     * @param st 状态
     */
    virtual void setState(ESelectionHandleState st);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief itemChange 图元变更
     * @param change 变更属性
     * @param value 变更的值
     * @return
     */
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

protected:
    typedef QVector<CSizeHandleRect *> Handles;
    Handles m_handles;  //选中时 显示的小方框

    bool m_bMutiSelectFlag; //设置选中状态 不用系统的选中方式，由自己管理
};

#endif // CGRAPHICSITEM_H

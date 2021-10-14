/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author: Zhang Hao<zhanghao@uniontech.com>
*
* Maintainer: Zhang Hao <zhanghao@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "cmanagerattributeservice.h"
#include "drawshape/cgraphicslineitem.h"
#include "drawshape/cgraphicsrectitem.h"
#include "drawshape/cgraphicsellipseitem.h"
#include "drawshape/cgraphicspolygonitem.h"
#include "drawshape/cgraphicstriangleitem.h"
#include "drawshape/cgraphicstextitem.h"
#include "drawshape/cgraphicspolygonalstaritem.h"
#include "drawshape/cgraphicsitemselectedmgr.h"
#include "drawshape/cgraphicspenitem.h"
#include "drawshape/cdrawscene.h"
#include "drawshape/cgraphicslineitem.h"
#include "drawshape/cgraphicsmasicoitem.h"

#include "frame/cundocommands.h"
#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"

#include <QGraphicsItem>
#include <QDebug>

CManagerAttributeService *CManagerAttributeService::instance = nullptr;
CManagerAttributeService *CManagerAttributeService::getInstance()
{
    if (nullptr == instance) {
        instance = new CManagerAttributeService();
    }
    return instance;
}

void CManagerAttributeService::showSelectedCommonProperty(CDrawScene *scence, QList<CGraphicsItem *> items)
{
    if (scence != nullptr) {
        m_currentScence = scence;
    }
    EGraphicUserType mode = EGraphicUserType::NoType;
    QMap<EDrawProperty, QVariant> propertys;//临时存放
    propertys.clear();
    if (items.size() <= 0) {
        return;
    } else {
        mode = static_cast<EGraphicUserType>(items.at(0)->type());
        switch (mode) {
        case RectType://矩形
            propertys[FillColor] = static_cast<CGraphicsRectItem *>(items.at(0))->brush();
            propertys[LineWidth] = static_cast<CGraphicsRectItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsRectItem *>(items.at(0))->pen().color();
            propertys[RectRadius] = static_cast<CGraphicsRectItem *>(items.at(0))->getXRedius();
            break;
        case EllipseType://圆形
            propertys[FillColor] = static_cast<CGraphicsEllipseItem *>(items.at(0))->brush();
            propertys[LineWidth] = static_cast<CGraphicsEllipseItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsEllipseItem *>(items.at(0))->pen().color();
            break;
        case TriangleType://三角形
            propertys[FillColor] = static_cast<CGraphicsTriangleItem *>(items.at(0))->brush();
            propertys[LineWidth] = static_cast<CGraphicsTriangleItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsTriangleItem *>(items.at(0))->pen().color();
            break;
        case PolygonalStarType://多角星
            propertys[FillColor] = static_cast<CGraphicsPolygonalStarItem *>(items.at(0))->brush();
            propertys[LineWidth] = static_cast<CGraphicsPolygonalStarItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsPolygonalStarItem *>(items.at(0))->pen().color();
            propertys[Anchors] = static_cast<CGraphicsPolygonalStarItem *>(items.at(0))->anchorNum();
            propertys[StarRadius] = static_cast<CGraphicsPolygonalStarItem *>(items.at(0))->innerRadius();
            break;
        case PolygonType://多边形
            propertys[FillColor] = static_cast<CGraphicsPolygonItem *>(items.at(0))->brush();
            propertys[LineWidth] = static_cast<CGraphicsPolygonItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsPolygonItem *>(items.at(0))->pen().color();
            propertys[SideNumber] = static_cast<CGraphicsPolygonItem *>(items.at(0))->nPointsCount();
            break;
        case LineType://线
            propertys[LineWidth] = static_cast<CGraphicsLineItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsLineItem *>(items.at(0))->pen().color();
            propertys[LineStartArrowType] = static_cast<CGraphicsLineItem *>(items.at(0))->getLineStartType();
            propertys[LineEndArrowType] = static_cast<CGraphicsLineItem *>(items.at(0))->getLineEndType();
            break;
        case PenType://画笔
            propertys[LineWidth] = static_cast<CGraphicsPenItem *>(items.at(0))->pen().width();
            propertys[LineColor] = static_cast<CGraphicsPenItem *>(items.at(0))->pen().color();
            propertys[PenLineArrowType] = static_cast<CGraphicsPenItem *>(items.at(0))->currentType();
            break;
        case TextType://文本
            propertys[TextColor] = static_cast<CGraphicsTextItem *>(items.at(0))->getTextColor();
            propertys[TextFont] = static_cast<CGraphicsTextItem *>(items.at(0))->getFont();
            qDebug() << "font11 = " << static_cast<CGraphicsTextItem *>(items.at(0))->getFont();
            propertys[TextSize] = static_cast<CGraphicsTextItem *>(items.at(0))->getFontSize();
            break;
        case BlurType://模糊
            break;
        default:
            break;
        }
    }
    QMap<EDrawProperty, QVariant> allPropertys;//信号中传递
    QVariant tmpVariant;
    tmpVariant.clear();
    for (int i = 1; i < items.size(); i++) {
        CGraphicsItem *item = items.at(i);
        item->setData(1, 1);
        allPropertys.clear();
        switch (static_cast<EGraphicUserType>(item->type())) {
        case RectType://矩形
            if (propertys.contains(FillColor)) {
                if (propertys[FillColor] == static_cast<CGraphicsRectItem *>(item)->brush()) {
                    allPropertys[FillColor] = propertys[FillColor];
                } else {
                    allPropertys[FillColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextColor)) {
                if (propertys[TextColor] == static_cast<CGraphicsRectItem *>(item)->brush().color()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsRectItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsRectItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            if (propertys.contains(RectRadius)) {
                if (propertys[RectRadius] == static_cast<CGraphicsRectItem *>(item)->getXRedius()) {
                    allPropertys[RectRadius] = propertys[RectRadius];
                } else {
                    allPropertys[RectRadius] = tmpVariant;
                }
            }
            break;
        case EllipseType://圆形
            if (propertys.contains(FillColor)) {
                if (propertys[FillColor] == static_cast<CGraphicsEllipseItem *>(item)->brush()) {
                    allPropertys[FillColor] = propertys[FillColor];
                } else {
                    allPropertys[FillColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextColor)) {
                if (propertys[TextColor] == static_cast<CGraphicsEllipseItem *>(item)->brush().color()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsEllipseItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsEllipseItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            break;
        case TriangleType://三角形
            if (propertys.contains(FillColor)) {
                if (propertys[FillColor] == static_cast<CGraphicsTriangleItem *>(item)->brush()) {
                    allPropertys[FillColor] = propertys[FillColor];
                } else {
                    allPropertys[FillColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextColor)) {
                if (propertys[TextColor] == static_cast<CGraphicsTriangleItem *>(item)->brush().color()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsTriangleItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsTriangleItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            break;
        case PolygonalStarType://多角星
            if (propertys.contains(FillColor)) {
                if (propertys[FillColor] == static_cast<CGraphicsPolygonalStarItem *>(item)->brush()) {
                    allPropertys[FillColor] = propertys[FillColor];
                } else {
                    allPropertys[FillColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextColor)) {
                if (propertys[TextColor] == static_cast<CGraphicsPolygonalStarItem *>(item)->brush().color()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsPolygonalStarItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsPolygonalStarItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(Anchors)) {
                if (propertys[Anchors] == static_cast<CGraphicsPolygonalStarItem *>(item)->anchorNum()) {
                    allPropertys[Anchors] = propertys[Anchors];
                } else {
                    allPropertys[Anchors] = tmpVariant;
                }
            }
            if (propertys.contains(StarRadius)) {
                if (propertys[StarRadius] == static_cast<CGraphicsPolygonalStarItem *>(item)->innerRadius()) {
                    allPropertys[StarRadius] = propertys[StarRadius];
                } else {
                    allPropertys[StarRadius] = tmpVariant;
                }
            }
            break;
        case PolygonType://多边形
            if (propertys.contains(FillColor)) {
                if (propertys[FillColor] == static_cast<CGraphicsPolygonItem *>(item)->brush()) {
                    allPropertys[FillColor] = propertys[FillColor];
                } else {
                    allPropertys[FillColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextColor)) {
                if (propertys[TextColor] == static_cast<CGraphicsPolygonItem *>(item)->brush().color()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsPolygonItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsPolygonItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            if (propertys.contains(SideNumber)) {
                if (propertys[SideNumber] == static_cast<CGraphicsPolygonItem *>(item)->nPointsCount()) {
                    allPropertys[SideNumber] = propertys[SideNumber];
                } else {
                    allPropertys[SideNumber] = tmpVariant;
                }
            }
            break;
        case LineType://线
            if (propertys.contains(LineStartArrowType)) {
                allPropertys[LineStartArrowType] = static_cast<CGraphicsLineItem *>(item)->getLineStartType();
            }
            if (propertys.contains(LineEndArrowType)) {
                allPropertys[LineEndArrowType] = static_cast<CGraphicsLineItem *>(item)->getLineEndType();
            }

            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsLineItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsLineItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            break;
        case PenType://画笔
            if (propertys.contains(PenLineArrowType)) {
                if (propertys[PenLineArrowType] == static_cast<CGraphicsPenItem *>(item)->currentType()) {
                    allPropertys[PenLineArrowType] = propertys[PenLineArrowType];
                } else {
                    allPropertys[PenLineArrowType] = tmpVariant;
                }
            }
            if (propertys.contains(LineWidth)) {
                if (propertys[LineWidth] == static_cast<CGraphicsPenItem *>(item)->pen().width()) {
                    allPropertys[LineWidth] = propertys[LineWidth];
                } else {
                    allPropertys[LineWidth] = tmpVariant;
                }
            }
            if (propertys.contains(LineColor)) {
                if (propertys[LineColor] == static_cast<CGraphicsPenItem *>(item)->pen().color()) {
                    allPropertys[LineColor] = propertys[LineColor];
                } else {
                    allPropertys[LineColor] = tmpVariant;
                }
            }
            break;
        case TextType://文本
            if (propertys.contains(TextColor)) {
                mode = EGraphicUserType::TextType;
                if (propertys[TextColor] == static_cast<CGraphicsTextItem *>(item)->getTextColor()) {
                    allPropertys[TextColor] = propertys[TextColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(FillColor)) {
                mode = EGraphicUserType::TextType;
                if (propertys[FillColor] == static_cast<CGraphicsTextItem *>(item)->getTextColor()) {
                    allPropertys[TextColor] = propertys[FillColor];
                } else {
                    allPropertys[TextColor] = tmpVariant;
                }
            }
            if (propertys.contains(TextFont)) {
                QFont font = static_cast<CGraphicsTextItem *>(item)->getFont();
                qDebug() << "font = " << font;
                if (propertys[TextFont].value<QFont>().family() == static_cast<CGraphicsTextItem *>(item)->getFont().family()) {
                    allPropertys[TextFont] = propertys[TextFont];
                } else {
                    allPropertys[TextFont] = tmpVariant;
                }
            }
            if (propertys.contains(TextSize)) {
                if (propertys[TextSize] == static_cast<CGraphicsTextItem *>(item)->getFontSize()) {
                    allPropertys[TextSize] = propertys[TextSize];
                } else {
                    allPropertys[TextSize] = tmpVariant;
                }
            }
            break;
        case BlurType://模糊
            break;
        default:
            break;
        }
        propertys = allPropertys;
    }
    if (allPropertys.size() == 0) {
        mode = EGraphicUserType::NoType;
    }
    emit signalShowWidgetCommonProperty(mode, allPropertys);
}

void CManagerAttributeService::refreshSelectedCommonProperty()
{
    if (m_currentScence) {
        this->showSelectedCommonProperty(m_currentScence, m_currentScence->getItemsMgr()->getItems());
    }
}

void CManagerAttributeService::setItemsCommonPropertyValue(EDrawProperty property, QVariant value)
{
    //todo
    return;
    if (m_currentScence && m_currentScence->getItemsMgr()) {
        if (m_currentScence->getItemsMgr()->getItems().size() > 1) {
            QUndoCommand *addCommand = new CSetItemsCommonPropertyValueCommand(m_currentScence, m_currentScence->getItemsMgr()->getItems(), property, value);
            CManageViewSigleton::GetInstance()->getCurView()->pushUndoStack(addCommand);
        }
    }
}

CManagerAttributeService::CManagerAttributeService()
{
    m_currentScence = nullptr;
}

void CManagerAttributeService::setLineStartType(CDrawScene *scence, ELineType startType)
{
    QList<QGraphicsItem *> allItems = scence->selectedItems();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        if (allItems.at(i)->zValue() == 0.0) {
            allItems.removeAt(i);
            continue;
        }
        if (allItems[i]->type() <= QGraphicsItem::UserType || allItems[i]->type() >= EGraphicUserType::MgrType) {
            allItems.removeAt(i);
        }
    }

    if (allItems.size() >= 1) {
        CGraphicsLineItem *lineItem = static_cast<CGraphicsLineItem *>(allItems.at(0));
        if (lineItem != nullptr) {
            scence->getDrawParam()->setLineStartType(startType);
            QUndoCommand *addCommand = new CSetLineAttributeCommand(scence, lineItem, true, startType);
            CManageViewSigleton::GetInstance()->getCurView()->pushUndoStack(addCommand);
            lineItem->calcVertexes();// 计算后将会自动调用更新，不再需要手动进行调用更新
        }
    }
}

void CManagerAttributeService::setLineEndType(CDrawScene *scence, ELineType endType)
{
    QList<QGraphicsItem *> allItems = scence->selectedItems();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        if (allItems.at(i)->zValue() == 0.0) {
            allItems.removeAt(i);
            continue;
        }
        if (allItems[i]->type() <= QGraphicsItem::UserType || allItems[i]->type() >= EGraphicUserType::MgrType) {
            allItems.removeAt(i);
        }
    }

    if (allItems.size() >= 1) {
        CGraphicsLineItem *lineItem = static_cast<CGraphicsLineItem *>(allItems.at(0));
        if (lineItem != nullptr) {
            scence->getDrawParam()->setLineEndType(endType);
            QUndoCommand *addCommand = new CSetLineAttributeCommand(scence, lineItem, false, endType);
            CManageViewSigleton::GetInstance()->getCurView()->pushUndoStack(addCommand);
            lineItem->calcVertexes(); // 计算后将会自动调用更新，不再需要手动进行调用更新
        }
    }
}

void CManagerAttributeService::updateSingleItemProperty(CDrawScene *scence, QGraphicsItem *item)
{
    Q_UNUSED(scence)
    if (item == nullptr) {
        return;
    }

    QMap<EDrawProperty, QVariant> propertys;

    switch (item->type()) {
    case TextType: {
        CGraphicsItem *cItem = nullptr;
        cItem = static_cast<CGraphicsItem *>(item);
        if (cItem == nullptr) {
            qDebug() << "convert to CGraphicsItem failed.";
            return;
        }

        CGraphicsTextItem *textItem = static_cast<CGraphicsTextItem *>(cItem);
        if (cItem == nullptr) {
            qDebug() << "convert to CGraphicsTextItem failed.";
            return;
        }

        bool isSameColor = textItem->getAllTextColorIsEqual();
        if (!isSameColor) {
            propertys.insert(TextColor, QColor());
        } else {
            propertys.insert(TextColor, textItem->getTextColor());
        }

        bool isSameSize = textItem->getAllFontSizeIsEqual();
        if (!isSameSize) {
            propertys.insert(TextSize, 0);
        } else {
            propertys.insert(TextSize, CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getTextSize());
        }

        bool isSameFamily = textItem->getAllFontFamilyIsEqual();
        if (!isSameFamily) {
            propertys.insert(TextFont, "");
        } else {
            propertys.insert(TextFont, CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getTextFont().family());
        }

        emit signalTextItemPropertyUpdate(propertys);
        break;
    }
    }
}

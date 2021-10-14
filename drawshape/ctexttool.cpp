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
#include "ctexttool.h"
#include "cdrawscene.h"
#include "cgraphicstextitem.h"
#include "cgraphicsproxywidget.h"
#include "cdrawparamsigleton.h"
#include "widgets/ctextedit.h"
#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QWidget>
#include <QGraphicsView>

CTextTool::CTextTool()
    : IDrawTool(text)
{

}

CTextTool::~CTextTool()
{

}

void CTextTool::mousePressEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    if (event->button() == Qt::LeftButton) {
        scene->clearSelection();
        m_sPointPress = event->scenePos();
        CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->setSingleFontFlag(true);
        QFont font = CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getTextFont();
        CGraphicsTextItem *item = new CGraphicsTextItem();
        //item->getTextEdit()->setText(tr("输入文本"));
        item->getTextEdit()->setText(QObject::tr("Input text here"));
        item->getTextEdit()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        item->setTextColor(CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getTextColor());
        item->getTextEdit()->selectAll();
//        item->setFont(font);

        QFontMetrics fm(font);
        QRect rect = fm.boundingRect(item->getTextEdit()->document()->toPlainText());


        item->setRect(QRectF(m_sPointPress.x(), m_sPointPress.y(), rect.width() * 1.2, rect.height() * 1.2));
        //item->setFont(CDrawParamSigleton::GetInstance()->getTextFont());
//        item->setTextColor(CDrawParamSigleton::GetInstance()->getTextColor());
        if (scene->sceneRect().right() - m_sPointPress.x() > 0) {
            item->setLastDocumentWidth(scene->sceneRect().right() - m_sPointPress.x());
        } else {
            item->setLastDocumentWidth(0);
        }

        item->setZValue(scene->getMaxZValue() + 1);
        scene->addItem(item);
        emit scene->itemAdded(item);
        item->setSelected(true);
        _tempTextItem = item;
//        scene->views()[0]->setFocus();
//        item->getTextEdit()->setFocus();
        //item->getCGraphicsProxyWidget()->setFocus();
        //
    } /*else if (event->button() == Qt::RightButton) {
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(selection);
        emit scene->signalChangeToSelect();
    } */else {
        scene->mouseEvent(event);
    }
}

void CTextTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    Q_UNUSED(scene)
    scene->mouseEvent(event);
}

void CTextTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, CDrawScene *scene)
{
    Q_UNUSED(scene)
    scene->mouseEvent(event);
    CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->setCurrentDrawToolMode(selection);
    emit scene->signalChangeToSelect();

    if (_tempTextItem != nullptr) {
        _tempTextItem->makeSelfEditable();
        _tempTextItem = nullptr;
    }
}

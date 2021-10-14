/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     Renran
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
#include "cgraphicsrotateangleitem.h"
#include "drawshape/cdrawparamsigleton.h"
#include "frame/cviewmanagement.h"

#include <QPainter>

CGraphicsRotateAngleItem::CGraphicsRotateAngleItem(qreal rotateAngle, qreal scale, QGraphicsItem *parent)
    : QGraphicsRectItem (parent)
    , m_rotateAngle(rotateAngle)
{
    m_width = 45.;
    m_height = 20.;
    m_fontSize = 11.;

    m_width = m_width / scale;
    m_height = m_height / scale;
    m_fontSize = m_fontSize / scale;
    m_textFont.setPointSizeF(m_fontSize);

    setRect(-m_width / 2, -m_height / 2, m_width, m_height);
}

CGraphicsRotateAngleItem::CGraphicsRotateAngleItem(const QRectF &rect, qreal rotateAngle, QGraphicsItem *parent)
    : QGraphicsRectItem (rect, parent)
    , m_rotateAngle(rotateAngle)

{
    setRect(rect);
}

void CGraphicsRotateAngleItem::updateRotateAngle(qreal rotateAngle)
{
    m_rotateAngle =  rotateAngle;
}

void CGraphicsRotateAngleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //painter->setPen(pen().width() == 0 ? Qt::NoPen : pen());
    painter->setPen(Qt::NoPen);
    if (CManageViewSigleton::GetInstance()->getThemeType() == 1) {
        painter->setBrush(QColor("#ececf8"));
    } else {
        painter->setBrush(QColor("#000000"));
    }

    painter->save();
    painter->setClipping(false);
    painter->drawRoundRect(rect());

    QString angle = QString("%1°").arg(QString::number(m_rotateAngle, 'f', 1));

    if (CManageViewSigleton::GetInstance()->getThemeType() == 1) {
        painter->setPen(Qt::black);
    } else {
        painter->setPen(Qt::white);
    }

    painter->setFont(m_textFont);

    painter->drawText(rect(), Qt::AlignCenter, angle);
    painter->restore();
}

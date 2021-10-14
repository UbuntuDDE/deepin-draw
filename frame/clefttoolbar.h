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
#ifndef RIGHTTOOLBAR_H
#define RIGHTTOOLBAR_H

#include <DFrame>
#include <DWidget>

class CCheckButton;
class QVBoxLayout;


DWIDGET_USE_NAMESPACE

class CLeftToolBar : public DFrame
{
    Q_OBJECT
public:
    explicit CLeftToolBar(DFrame *parent = nullptr);
    ~CLeftToolBar();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *event);                      //进入QWidget瞬间事件


signals:
    /**
     * @brief setCurrentDrawTool 设置当前画图工具信号
     * @param type　画图工具类型
     */
    void setCurrentDrawTool(int type);
    /**
     * @brief importPic　导入图片信号
     */
    void importPic();
    /**
     * @brief signalBegainCut　开始裁剪信号
     */
    void signalBegainCut();
    /**
     * @brief singalDoCutFromLeftToolBar　点击左边工具栏执行裁剪信号
     */
    void singalDoCutFromLeftToolBar();

public slots:
    /**
     * @brief slotAfterQuitCut　退出裁剪后更新工具栏
     */
    void slotAfterQuitCut();
    /**
     * @brief changeButtonTheme　改变工具栏按钮主题
     */
    void changeButtonTheme();
    /**
     * @brief slotShortCutSelect　选择按钮快捷键功能
     */
    void slotShortCutSelect(bool showToolMidWidget = true);

private slots:
    /**
     * @brief slotShortCutPictrue　选择按钮快捷键
     */
    void slotShortCutPictrue();
    /**
     * @brief slotShortCutRect　矩形按钮快捷键
     */
    void slotShortCutRect();
    /**
     * @brief slotShortCutRound　圆形按钮快捷键
     */
    void slotShortCutRound();
    /**
     * @brief slotShortCutTriangle　三角形按钮快捷键
     */
    void slotShortCutTriangle();
    /**
     * @brief slotShortCutPolygonalStar　星型按钮快捷键
     */
    void slotShortCutPolygonalStar();
    /**
     * @brief slotShortCutPolygon　多边形按钮快捷键
     */
    void slotShortCutPolygon();
    /**
     * @brief slotShortCutLine　线段按钮快捷键
     */
    void slotShortCutLine();
    /**
     * @brief slotShortCutPen　画笔按钮快捷键
     */
    void slotShortCutPen();
    /**
     * @brief slotShortCutText　文字按钮快捷键
     */
    void slotShortCutText();
    /**
     * @brief slotShortCutBlur　模糊按钮快捷键
     */
    void slotShortCutBlur();
    /**
     * @brief slotShortCutCut　裁剪按钮快捷键
     */
    void slotShortCutCut();
    /**
     * @brief slotClearToolSelection　清除工具栏选中状态
     */
    void slotClearToolSelection();

private:
    QList<CCheckButton *> m_actionButtons;
    CCheckButton *m_selectBtn;
    CCheckButton *m_picBtn;
    CCheckButton *m_rectBtn;
    CCheckButton *m_roundBtn;
    CCheckButton *m_triangleBtn;
    CCheckButton *m_starBtn;
    CCheckButton *m_polygonBtn;
    CCheckButton *m_lineBtn;
    CCheckButton *m_penBtn;
    CCheckButton *m_textBtn;
    CCheckButton *m_blurBtn;
    CCheckButton *m_cutBtn;

    QVBoxLayout *m_layout;

    QAction *m_selectAction;
    QAction *m_pictureAction;
    QAction *m_rectAction;
    QAction *m_roundAction;
    QAction *m_triangleAction;
    QAction *m_starAction;
    QAction *m_polygonAction;
    QAction *m_lineAction;
    QAction *m_penAction;
    QAction *m_textAction;
    QAction *m_blurAction;
    QAction *m_cutAction;
//    CCentralwidget *m_parentWidget;


private:
    /**
     * @brief initUI　初始化ＵＩ
     */
    void initUI();
    /**
     * @brief initConnection　初始化连接
     */
    void initConnection();
    /**
     * @brief clearOtherSelections　清除其他按钮选中
     * @param clickedButton
     */
    void clearOtherSelections(CCheckButton *clickedButton);
    /**
     * @brief initDrawTools　初始化画图工具
     */
    void initDrawTools();
    /**
     * @brief initShortCut　初始化快捷键ａｃｔｉｏｎ
     */
    void initShortCut();
    /**
     * @brief initShortCutConnection　初始化快捷键连接
     */
    void initShortCutConnection();
    /**
     * @brief isCutMode 判断当前是不是裁剪模式　如果是先退出裁剪
     */
    void isCutMode();
};

#endif // RIGHTTOOLBAR_H

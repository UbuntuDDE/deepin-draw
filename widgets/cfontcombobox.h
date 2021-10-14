#ifndef CFONTCOMBOBOX_H
#define CFONTCOMBOBOX_H
#include <DFontComboBox>
DWIDGET_USE_NAMESPACE
class CFontComboBox : public DFontComboBox
{
    Q_OBJECT
public:
    CFontComboBox(QWidget *parent = nullptr);
    virtual void hidePopup() Q_DECL_OVERRIDE;

signals:
    void signalhidepopup();
};

#endif // CFONTCOMBOBOX_H

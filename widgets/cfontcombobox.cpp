#include "cfontcombobox.h"

CFontComboBox::CFontComboBox(QWidget *parent)
    : DFontComboBox(parent)
{

}

void CFontComboBox::hidePopup()
{
    DFontComboBox::hidePopup();
    emit signalhidepopup();
}

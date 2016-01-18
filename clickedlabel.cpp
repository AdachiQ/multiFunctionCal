#include "clickedlabel.h"

void ClickedLabel::mouseReleaseEvent(QMouseEvent *evt)
{
    emit clicked(this);
}

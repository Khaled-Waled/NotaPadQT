#include "loadbackgrounddialog.h"
#include <iostream>

LoadBackgroundDialog::LoadBackgroundDialog(QWidget * parent,
                                            QString caption,
                                            QString dir,
                                            QString filter)
    :QFileDialog(parent, caption, dir, filter)
{
    ;
}

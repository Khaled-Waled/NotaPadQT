#ifndef LOADBACKGROUNDDIALOG_H
#define LOADBACKGROUNDDIALOG_H

namespace Ui{
    class LoadBackgroundDialog;
}

#include <QFileDialog>
#include "filemanager.h"

class LoadBackgroundDialog: public QFileDialog
{
    Q_OBJECT
public:
    LoadBackgroundDialog(QWidget * parent,
                         QString caption,
                         QString dir,
                         QString filter);
};



#endif // LOADBACKGROUNDDIALOG_H
#ifndef ADDTOPICDIALOG_H
#define ADDTOPICDIALOG_H

#include <QDialog>

namespace Ui {
class addTopicDialog;
}

class addTopicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addTopicDialog(QWidget *parent = nullptr);
    ~addTopicDialog();

private:
    Ui::addTopicDialog *ui;
};

#endif // ADDTOPICDIALOG_H

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

    QString GetTopic();

private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::addTopicDialog *ui;

    QString topic;
};

#endif // ADDTOPICDIALOG_H

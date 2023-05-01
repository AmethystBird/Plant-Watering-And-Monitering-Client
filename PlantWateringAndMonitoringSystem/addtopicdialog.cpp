#include "addtopicdialog.h"
#include "ui_addtopicdialog.h"
#include <QMessageBox>

addTopicDialog::addTopicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTopicDialog)
{
    ui->setupUi(this);
}

addTopicDialog::~addTopicDialog()
{
    delete ui;
}

void addTopicDialog::on_applyButton_clicked()
{
    if (ui->topicLineEdit->text() == "")
    {
        QMessageBox::information(this, QLatin1String("Error"), QLatin1String("A topic must be inputted in order to subscribe to it."));
        return;
    }
    done(1);
}


void addTopicDialog::on_cancelButton_clicked()
{
    done(0);
}

QString addTopicDialog::GetTopic()
{
    return ui->topicLineEdit->text();
}

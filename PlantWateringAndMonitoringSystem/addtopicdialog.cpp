#include "addtopicdialog.h"
#include "ui_addtopicdialog.h"

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

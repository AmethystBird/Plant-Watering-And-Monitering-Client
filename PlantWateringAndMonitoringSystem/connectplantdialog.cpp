#include "connectplantdialog.h"
#include "ui_connectplantdialog.h"
#include "QMessageBox"

ConnectPlantDialog::ConnectPlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectPlantDialog)
{
    ui->setupUi(this);
}

ConnectPlantDialog::~ConnectPlantDialog()
{
    delete ui;
}

Ui::ConnectPlantDialog* ConnectPlantDialog::GetUI()
{
    return ui;
}

void ConnectPlantDialog::on_applyButton_clicked()
{
    done(1);
}

void ConnectPlantDialog::on_cancelButton_clicked()
{
    done(0);
}

QString ConnectPlantDialog::GetHostname()
{
    return ui->hostnameLineEdit->text();;
}

quint16 ConnectPlantDialog::GetPort()
{
    const QString portInput = ui->portLineEdit->text();
    port = portInput.toInt();
    return port;
}

QString ConnectPlantDialog::GetClientID()
{
    return ui->clientIDLineEdit->text();
}

QString ConnectPlantDialog::GetUsername()
{
    return ui->usernameLineEdit->text();
}

QString ConnectPlantDialog::GetPassword()
{
    return ui->passwordLineEdit->text();
}

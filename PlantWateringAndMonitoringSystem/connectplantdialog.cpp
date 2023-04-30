#include "connectplantdialog.h"
#include "ui_connectplantdialog.h"

//#include "mainwindow.h"
//#include "main.cpp"
//#include <QMainWindow>

#include "QMessageBox"

ConnectPlantDialog::ConnectPlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectPlantDialog)
{
    ui->setupUi(this);
    //w = (MainWindow*)parent;

    //Signals
    //QObject::connect(ui->applyButton, SIGNAL(clicked()), this, SIGNAL(CredentialsApplied())); //Connects click event of apply button to credentials applied function
}

ConnectPlantDialog::~ConnectPlantDialog()
{
    delete ui;
}

Ui::ConnectPlantDialog* ConnectPlantDialog::GetUI()
{
    return ui;
}

/*void ConnectPlantDialog::SetMainWindow(MainWindow* MainWindowIn)
{
    w = MainWindowIn;
}*/

void ConnectPlantDialog::on_applyButton_clicked()
{
    /*if (!w)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Can't proceed to establish a connection because MainWindow address could not be acquired."));
        return;
    }
    if (!w->GetMQTTPlantClient())
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Can't proceed to establish a connection because QMqttClient was never instantiated."));
        return;
    }*/

    //Sort these credentials
    hostname = ui->hostnameLineEdit->text();
    const QString portInput = ui->portLineEdit->text();
    port = portInput.toInt();
    clientID = ui->clientIDLineEdit->text();
    username = ui->usernameLineEdit->text();
    password = ui->passwordLineEdit->text();

    //QMessageBox::information(this, QLatin1String("Error"), QLatin1String("Can't proceed to establish a connection because QMqttClient was never instantiated."));

    done(1);
}

void ConnectPlantDialog::on_cancelButton_clicked()
{
    done(0);

    //Apparent other options
    //accepted();
    //reject();
    //done(0);
    //finished(0);
    //close();
}

QString ConnectPlantDialog::GetHostname()
{
    return hostname;
}

quint16 ConnectPlantDialog::GetPort()
{
    return port;
}

QString ConnectPlantDialog::GetClientID()
{
    return clientID;
}

QString ConnectPlantDialog::GetUsername()
{
    return username;
}

QString ConnectPlantDialog::GetPassword()
{
    return password;
}

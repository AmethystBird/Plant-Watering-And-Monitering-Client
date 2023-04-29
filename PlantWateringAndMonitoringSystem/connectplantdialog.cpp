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
    QObject::connect(ui->applyButton, SIGNAL(clicked()), this, SIGNAL(CredentialsApplied())); //Connects click event of apply button to credentials applied function
}

ConnectPlantDialog::~ConnectPlantDialog()
{
    delete ui;
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
    const QString hostname = ui->hostnameLineEdit->text();
    //w->GetMQTTPlantClient()->setHostname(hostname);

    const QString port = ui->portLineEdit->text();
    quint16 portFormatted = port.toInt();
    //w->GetMQTTPlantClient()->setPort(portFormatted);

    const QString clientID = ui->clientIDLineEdit->text();
    //w->GetMQTTPlantClient()->setClientId(clientID);

    const QString username = ui->usernameLineEdit->text();
    //w->GetMQTTPlantClient()->setUsername(username);

    const QString password = ui->passwordLineEdit->text();
    //w->GetMQTTPlantClient()->setPassword(password);

    //w->GetMQTTPlantClient()->connectToHost();

    //QMessageBox::information(this, QLatin1String("Error"), QLatin1String("Can't proceed to establish a connection because QMqttClient was never instantiated."));

    close();
}

void ConnectPlantDialog::on_cancelButton_clicked()
{
    close();

    //Apparent other options
    //reject();
    //done(0);
    //finished(0);
}

/*void ConnectPlantDialog::CredentialsApplied()
{

}*/

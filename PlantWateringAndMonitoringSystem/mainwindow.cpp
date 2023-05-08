#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtMqtt/QtMqtt>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), connectPlantDialogBox(this), addTopicDialogBox(this)
{
    ui->setupUi(this);

    displayMode = false;
    ToggleDisplayMode();
    ui->darkModeCheckBox->setChecked(true);

    series = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("<Sensor Value>");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setUpdatesEnabled(true);

    ui->verticalLayout->addWidget(chartView);

    //MQTT
    //ui->telemetryDebugLabel->setStyleSheet("color: #ff0080");
    CreateMQTTClient();

    seriesToDisplay = 0;
}

MainWindow::~MainWindow()
{
    if (MQTTPlantClient->Connected)
    {
        MQTTPlantClient->disconnectFromHost();
    }
    delete ui;
}

void MainWindow::ToggleDisplayMode()
{
    displayMode = !displayMode;
    if (displayMode)
    {
        setStyleSheet("background-color: #101010");
        ui->titleLabel->setStyleSheet("color: #f0f0f0");
        ui->optionsLabel->setStyleSheet("color: #e0e0e0");
        ui->networkingLabel->setStyleSheet("color: #e0e0e0");
        ui->preferencesLabel->setStyleSheet("color: #e0e0e0");
        ui->connectPlantButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->addTopicButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->darkModeCheckBox->setStyleSheet("color: #e0e0e0");
        ui->hideOnCloseCheckBox->setStyleSheet("color: #e0e0e0");
        ui->sendNotificationsCheckBox->setStyleSheet("color: #e0e0e0");
        ui->lightButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->moistureButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->humidityButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->temperatureButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->optionsButton->setStyleSheet("QToolButton {background-color: #202020; color: #e0e0e0;}");

        //Connect plant dialog
        //Ui::ConnectPlantDialog* connectPlantDialogUI = dlg.GetUI();
        //connectPlantDialogUI->applyButton;
    }
    else
    {
        setStyleSheet("background-color: #f0f0f0");
        ui->titleLabel->setStyleSheet("color: #101010");
        ui->optionsLabel->setStyleSheet("color: #202020");
        ui->networkingLabel->setStyleSheet("color: #202020");
        ui->preferencesLabel->setStyleSheet("color: #202020");
        ui->connectPlantButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->addTopicButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->darkModeCheckBox->setStyleSheet("color: #202020");
        ui->hideOnCloseCheckBox->setStyleSheet("color: #202020");
        ui->sendNotificationsCheckBox->setStyleSheet("color: #202020");
        ui->lightButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->moistureButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->humidityButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->temperatureButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->optionsButton->setStyleSheet("QToolButton {background-color: #e0e0e0; color: #202020;}");
    }
}

void MainWindow::on_optionsButton_released()
{
    ui->widget->setVisible(!ui->widget->isVisible());
    ui->optionsLabel->setVisible(!ui->optionsLabel->isVisible());
}

void MainWindow::on_darkModeCheckBox_released()
{
    ToggleDisplayMode();
}

/*
void MainWindow::DebugMQTT()
{
    //MQTT subscription setup
    MQTTPlantClient = new QMqttClient(this);
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not instantiate QMqttClient"));
        return;
    }
    //MQTTPlantSubscription = new QMqttSubscription();

    //Sort these credentials
    const QString hostname = "192.168.1.6";
    MQTTPlantClient->setHostname(hostname);

    //MQTTPlantClient->setPort(quint16(1883));
    quint16 port = 1883;
    MQTTPlantClient->setPort(port);

    const QString clientID = "qt01";
    MQTTPlantClient->setClientId(clientID);

    const QString username = "qtapp";
    MQTTPlantClient->setUsername(username);

    const QString password = "1234";
    MQTTPlantClient->setPassword(password);

    //connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    //connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    //connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
    //connect(MQTTPlantClient, &QMqttClient::pingResponseReceived, this, &MainWindow::Pinged);

    MQTTPlantClient->connectToHost();
    //Subscribe();
}
*/

void MainWindow::CreateMQTTClient()
{
    //MQTT subscription setup
    MQTTPlantClient = new QMqttClient(this);
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not instantiate QMqttClient"));
        return;
    }

    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
    connect(MQTTPlantClient, &QMqttClient::pingResponseReceived, this, &MainWindow::Pinged);
}

/*void MainWindow::Subscribe(QString topic)
{
    if (topic == "chilli/light")
    {
        if (!MQTTLightSubscription)
        {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        MQTTLightSubscription = MQTTPlantClient->subscribe(topic, 0); //0; message loss can occur
    }
    else if (topic == "chilli/temperature")
    {
        if (!MQTTTemperatureSubscription)
        {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        MQTTTemperatureSubscription = MQTTPlantClient->subscribe(topic, 0); //0; message loss can occur
    }
    else if (topic == "chilli/humidity")
    {
        if (!MQTTHumiditySubscription)
        {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        MQTTHumiditySubscription = MQTTPlantClient->subscribe(topic, 0); //0; message loss can occur
    }
    else if (topic == "chilli/moisture")
    {
        if (!MQTTMoistureSubscription)
        {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        MQTTMoistureSubscription = MQTTPlantClient->subscribe(topic, 0); //0; message loss can occur
    }
}*/

void MainWindow::StateChanged()
{
    quint16 state = MQTTPlantClient->state();
    //Only subscribe once state is '2,' otherwise race condition between connection & subscription may occur
    switch(state) {
    case 2:
        MQTTLightSubscription = MQTTPlantClient->subscribe(QMqttTopicFilter{"chilli/#"}, 0); //0; message loss can occur
        break;
    default:
        break;
    }
}

void MainWindow::Disconnected()
{
    QMessageBox::information(this, QLatin1String("Disconnection"), QLatin1String("Broker server disconnected from client."));
}

void MainWindow::Received(const QByteArray &message, const QMqttTopicName &topic)
{
    if (topic.name() != "chilli/light" && topic.name() != "chilli/temperature" && topic.name() != "chilli/humidity" && topic.name() != "chilli/moisture")
    {
        return;
    }

    QString value = "";
    QString hours = "";
    QString minutes = "";
    QString seconds = "";

    for (quint16 i = 0; i < message.size(); i++)
    {
        if (message[i] == 'V')
        {
            i+=3;

            while (message[i] != ' ')
            {
                value+= message[i];
                i++;
            }
        }
        else if (message[i] == 'H')
        {
            i+=3;

            while (message[i] != ' ')
            {
                hours+= message[i];
                i++;
            }
        }
        else if (message[i] == 'M')
        {
            i+=3;

            while (message[i] != ' ')
            {
                minutes+= message[i];
                i++;
            }
        }
        else if (message[i] == 'S')
        {
            i+=3;

            while (i != message.size())
            {
                seconds+= message[i];
                i++;
            }
        }
    }

    float valueDisplay = value.toFloat();
    QTime timeDisplay(hours.toInt(), minutes.toInt(), seconds.toInt());

    //Append data
    if (topic.name() == "chilli/light")
    {
        if (seriesValuesLight.size() > 63) //& by implication 'seriesTimesLight'
        {
            seriesValuesLight.erase(seriesValuesLight.begin(), seriesValuesLight.begin()+1);
            seriesTimesLight.erase(seriesTimesLight.begin(), seriesTimesLight.begin()+1);
        }
        seriesValuesLight.push_back(valueDisplay);
        seriesTimesLight.push_back(timeDisplay.msecsSinceStartOfDay());
    }
    else if (topic.name() == "chilli/temperature")
    {
        if (seriesValuesTemperature.size() > 63)
        {
            seriesValuesTemperature.erase(seriesValuesTemperature.begin(), seriesValuesTemperature.begin()+1);
            seriesTimesTemperature.erase(seriesTimesTemperature.begin(), seriesTimesTemperature.begin()+1);
        }
        seriesValuesTemperature.push_back(valueDisplay);
        seriesTimesTemperature.push_back(timeDisplay.msecsSinceStartOfDay());
    }
    else if (topic.name() == "chilli/humidity")
    {
        if (seriesValuesHumidity.size() > 63)
        {
            seriesValuesHumidity.erase(seriesValuesHumidity.begin(), seriesValuesHumidity.begin()+1);
            seriesTimesHumidity.erase(seriesTimesHumidity.begin(), seriesTimesHumidity.begin()+1);
        }
        seriesValuesHumidity.push_back(valueDisplay);
        seriesTimesHumidity.push_back(timeDisplay.msecsSinceStartOfDay());
    }
    else if (topic.name() == "chilli/moisture")
    {
        if (seriesValuesMoisture.size() > 63)
        {
            seriesValuesMoisture.erase(seriesValuesMoisture.begin(), seriesValuesMoisture.begin()+1);
            seriesTimesMoisture.erase(seriesTimesMoisture.begin(), seriesTimesMoisture.begin()+1);
        }
        seriesValuesMoisture.push_back(valueDisplay);
        seriesTimesMoisture.push_back(timeDisplay.msecsSinceStartOfDay());
    }
    else {
        return;
    }

    RefreshGraph();
}

void MainWindow::Pinged()
{
    //No particular requirements
    QMessageBox::information(this, QLatin1String("Ping"), QLatin1String("Ping."));
}

void MainWindow::on_connectPlantButton_clicked()
{
    if (ui->connectPlantButton->text() == "Connect Plant") //Connect to MQTT server
    {
        connectPlantDialogBox.setModal(true);
        int result = connectPlantDialogBox.exec();
        if (result == 1)
        {
            if (!MQTTPlantClient)
            {
                QMessageBox::critical(this, QLatin1String("Error in on_connectPlantButton_clicked()"), QLatin1String("Could not instantiate QMqttClient"));
                return;
            }
            MQTTPlantClient->setHostname(connectPlantDialogBox.GetHostname());
            MQTTPlantClient->setPort(connectPlantDialogBox.GetPort());
            MQTTPlantClient->setClientId(connectPlantDialogBox.GetClientID());
            MQTTPlantClient->setUsername(connectPlantDialogBox.GetUsername());
            MQTTPlantClient->setPassword(connectPlantDialogBox.GetPassword());

            qInfo() << "Connecting to host";
            qInfo() << MQTTPlantClient->hostname();
            qInfo() << MQTTPlantClient->port();
            qInfo() << MQTTPlantClient->clientId();
            qInfo() << MQTTPlantClient->username();
            qInfo() << MQTTPlantClient->password();
            MQTTPlantClient->connectToHost();

            if (!MQTTLightSubscription)
            {
                QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
                return;
            }

            ui->connectPlantButton->setText("Disconnect Plant");
        }
    }
    else //Disconnect from MQTT server
    {
        MQTTPlantClient->disconnectFromHost();
        ui->connectPlantButton->setText("Connect Plant");
    }
}

void MainWindow::on_addTopicButton_clicked()
{
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("No connection has been established to an MQTT server."));
        return;
    }
}

void MainWindow::RefreshGraph()
{
    series = new QLineSeries();

    if (seriesToDisplay == 0) //light
    {
        for (int i = 0; i < seriesValuesLight.size(); i++) //& by implication 'seriesTimes'
        {
            series->append(seriesTimesLight[i], seriesValuesLight[i]);
        }
    }
    else if (seriesToDisplay == 1) //temperature
    {
        for (int i = 0; i < seriesValuesTemperature.size(); i++)
        {
            series->append(seriesTimesTemperature[i], seriesValuesTemperature[i]);
        }
    }
    else if (seriesToDisplay == 2) //humidity
    {
        for (int i = 0; i < seriesValuesHumidity.size(); i++)
        {
            series->append(seriesTimesHumidity[i], seriesValuesHumidity[i]);
        }
    }
    else if (seriesToDisplay == 3) //moisture
    {
        for (int i = 0; i < seriesValuesMoisture.size(); i++)
        {
            series->append(seriesTimesMoisture[i], seriesValuesMoisture[i]);
        }
    }
    else {
        return;
    }

    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->update();
}

void MainWindow::on_lightButton_clicked()
{
    if (seriesToDisplay != 0)
    {
        seriesToDisplay = 0;
        RefreshGraph();
    }
}


void MainWindow::on_moistureButton_clicked()
{
    if (seriesToDisplay != 3)
    {
        seriesToDisplay = 3;
        RefreshGraph();
    }
}


void MainWindow::on_temperatureButton_clicked()
{
    if (seriesToDisplay != 1)
    {
        seriesToDisplay = 1;
        RefreshGraph();
    }
}


void MainWindow::on_humidityButton_clicked()
{
    if (seriesToDisplay != 2)
    {
        seriesToDisplay = 2;
        RefreshGraph();
    }
}


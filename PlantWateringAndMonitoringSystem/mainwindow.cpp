#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtMqtt/QtMqtt>
//#include <QtMqtt/QMqttSubscription>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displayMode = false;
    ToggleDisplayMode();
    ui->darkModeCheckBox->setChecked(true);

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(chartView);

    //MQTT
    CreateMQTTClient();
    Subscribe();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ToggleDisplayMode()
{
    displayMode = !displayMode;
    if (displayMode)
    {
        setStyleSheet("background-color: #101010");
        ui->titleLabel->setStyleSheet("color: #f0f0f0");
        //ui->optionsMenuFrame->setVisible(false);
        //ui->optionsMenuFrame->setStyleSheet("background-color: #202020");
        ui->optionsLabel->setStyleSheet("color: #e0e0e0");
        ui->networkingLabel->setStyleSheet("color: #e0e0e0");
        ui->preferencesLabel->setStyleSheet("color: #e0e0e0");
        ui->disconnectPlantButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->forgetPlantButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->darkModeCheckBox->setStyleSheet("color: #e0e0e0");
        ui->hideOnCloseCheckBox->setStyleSheet("color: #e0e0e0");
        ui->sendNotificationsCheckBox->setStyleSheet("color: #e0e0e0");
        ui->lightButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->moistureButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->humidityButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->temperatureButton->setStyleSheet("QPushButton {background-color: #202020; color: #e0e0e0;}");
        ui->optionsButton->setStyleSheet("QToolButton {background-color: #202020; color: #e0e0e0;}");
    }
    else
    {
        setStyleSheet("background-color: #f0f0f0");
        ui->titleLabel->setStyleSheet("color: #101010");
        //ui->optionsMenuFrame->setVisible(false);
        //ui->optionsMenuFrame->setStyleSheet("background-color: #e0e0e0");
        ui->optionsLabel->setStyleSheet("color: #202020");
        ui->networkingLabel->setStyleSheet("color: #202020");
        ui->preferencesLabel->setStyleSheet("color: #202020");
        ui->disconnectPlantButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
        ui->forgetPlantButton->setStyleSheet("QPushButton {background-color: #e0e0e0; color: #202020;}");
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
    //ui->optionsMenuFrame->setVisible(!ui->optionsMenuFrame->isVisible());
    ui->widget->setVisible(!ui->widget->isVisible());
    ui->optionsLabel->setVisible(!ui->optionsLabel->isVisible());
}

void MainWindow::on_darkModeCheckBox_released()
{
    ToggleDisplayMode();
}

void MainWindow::CreateMQTTClient()
{
    //MQTT subscription setup
    MQTTPlantClient = new QMqttClient(this);
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not instamntiate QMqttClient?"));
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

    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    //connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
    connect(MQTTPlantClient, &QMqttClient::pingResponseReceived, this, &MainWindow::Pinged);

    //test
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" Received Topic: ")
                                + topic.name()
                                + QLatin1String(" Message: ")
                                + message
                                + QLatin1Char('\n');
        ui->telemetryDebugLabel->setText(content);
    });

    MQTTPlantClient->connectToHost();
}

void MainWindow::Subscribe()
{
    if (!MQTTPlantSubscription)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
    else {
        QMessageBox::information(this, QLatin1String("Success"), QLatin1String("Successfully subscribed!"));
    }

    //const QMqttTopicFilter* topic = new QMqttTopicFilter("chilli/light");
    //auto topic = new QMqttTopicFilter("chilli/light");

    const QString topic2 = "chilli/light";
    MQTTPlantSubscription = MQTTPlantClient->subscribe(topic2, 0); //0; message loss can occur
}

void MainWindow::ReceiveTest()
{
    //QString telemetry = MQTTPlantSubscription->topic().filter();
    //ui->titleLabel->setText(telemetry);
}

//Update telemetry
void MainWindow::StateChanged()
{
    receivedTelemetry = MQTTPlantClient->state();
    ui->titleLabel->setText(QString::number(receivedTelemetry));
}

void MainWindow::Disconnected()
{
    //No particular requirements
    QMessageBox::information(this, QLatin1String("Disconnection"), QLatin1String("Broker server disconnected from client."));
}

void MainWindow::Received(const QByteArray &message, const QMqttTopicName &topic)
{
    //No particular requirements
    //QMessageBox::information(this, QLatin1String("Received()"), QLatin1String("messageReceived() >> Received()"));

    ui->telemetryDebugLabel->setText((const QString)message);
}

void MainWindow::Pinged()
{
    //No particular requirements
    QMessageBox::information(this, QLatin1String("Ping"), QLatin1String("Ping."));
}
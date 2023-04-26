#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtMqtt/qmqttclient.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_optionsButton_released();

    void on_darkModeCheckBox_released();

private:
    Ui::MainWindow *ui;

    void ToggleDisplayMode();
    bool displayMode;

    QMqttClient* MQTTPlantClient;
    QMqttSubscription* MQTTPlantSubscription;

    void CreateMQTTClient();
    void Subscribe();
    void ReceiveTest();

    //Tagged methods
    void StateChanged();
    void Disconnected();
    void Received(const QByteArray &message, const QMqttTopicName &topic);
    void Pinged();

    qint16 receivedTelemetry;
};
#endif // MAINWINDOW_H

/*
    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
*/
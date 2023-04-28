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

    QMqttClient* GetMQTTPlantClient();

private slots:
    void on_optionsButton_released();

    void on_darkModeCheckBox_released();

    void on_connectPlantButton_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient* MQTTPlantClient;
    QMqttSubscription* MQTTPlantSubscription;

    void ToggleDisplayMode();
    bool displayMode;

    void CreateMQTTClient();
    void Subscribe();
    void ReceiveTest();

    //Callback bound methods
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtMqtt/qmqttclient.h"
#include "addtopicdialog.h"
#include "connectplantdialog.h"
#include "qchart.h"
#include "qchartview.h"
#include "qlineseries.h"
#include <QMainWindow>
#include <queue>

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

    void on_addTopicButton_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient* MQTTPlantClient;
    QMqttSubscription* MQTTPlantSubscription;

    void ToggleDisplayMode();
    bool displayMode;

    void CreateMQTTClient();
    void Subscribe(QString topic);
    void ReceiveTest();
    void DebugMQTT();

    //Callback bound methods
    void StateChanged();
    void Disconnected();
    void Received(const QByteArray &message, const QMqttTopicName &topic);
    void Pinged();

    qint16 receivedTelemetry;

    ConnectPlantDialog connectPlantDialogBox;
    addTopicDialog addTopicDialogBox;

    //Chart
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    std::vector<float> seriesValues;
    std::vector<int> seriesTimes;
};
#endif // MAINWINDOW_H

/*
    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
*/

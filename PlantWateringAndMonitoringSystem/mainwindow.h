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
//#include <map> //doesn't appear to be necessary

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Topic {
public:
    std::vector<float> seriesValues;
    std::vector<int> seriesTimes;
};

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

    void on_lightButton_clicked();

    void on_moistureButton_clicked();

    void on_temperatureButton_clicked();

    void on_humidityButton_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient* MQTTPlantClient;
    QMqttSubscription* MQTTPlantSubscription;

    void ToggleDisplayMode();
    bool displayMode;

    void CreateMQTTClient();
    void Subscribe(QString topic);
    void Unsubscribe(QString topic);
    void ReceiveTest();
    void DebugMQTT();
    void RefreshGraph();

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

    //Come back to this if time
    //std::map<QString, Topic> topics;
    //QMap<QString, Topic> topics;

    //For not dynamic version
    int seriesToDisplay;

    std::vector<float> seriesValuesLight;
    std::vector<int> seriesTimesLight;

    std::vector<float> seriesValuesTemperature;
    std::vector<int> seriesTimesTemperature;

    std::vector<float> seriesValuesHumidity;
    std::vector<int> seriesTimesHumidity;

    std::vector<float> seriesValuesMoisture;
    std::vector<int> seriesTimesMoisture;
};

#endif // MAINWINDOW_H

/*
    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
*/

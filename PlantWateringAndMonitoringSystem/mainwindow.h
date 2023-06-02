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

    void on_lightButton_clicked();

    void on_moistureButton_clicked();

    void on_temperatureButton_clicked();

    void on_humidityButton_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient* MQTTPlantClient;
    QMqttSubscription* MQTTLightSubscription;
    QMqttSubscription* MQTTTemperatureSubscription;
    QMqttSubscription* MQTTHumiditySubscription;
    QMqttSubscription* MQTTMoistureSubscription;

    void ToggleDisplayMode();
    bool displayMode;

    void CreateMQTTClient();
    void RefreshGraph();

    //Callback bound methods
    void StateChanged();
    void Disconnected();
    void Received(const QByteArray &message, const QMqttTopicName &topic);
    void Pinged();

    ConnectPlantDialog connectPlantDialogBox;
    addTopicDialog addTopicDialogBox;

    //Chart
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;

    std::vector<float> seriesValuesLight;
    //std::vector<QString> seriesTimesLight;
    std::vector<int> seriesTimesLight;

    std::vector<float> seriesValuesTemperature;
    std::vector<int> seriesTimesTemperature;

    std::vector<float> seriesValuesHumidity;
    std::vector<int> seriesTimesHumidity;

    std::vector<float> seriesValuesMoisture;
    std::vector<int> seriesTimesMoisture;

    int seriesToDisplay;
};
#endif // MAINWINDOW_H

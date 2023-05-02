#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtMqtt/QtMqtt>
//#include <QtMqtt/QMqttSubscription>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), connectPlantDialogBox(this), addTopicDialogBox(this)
{
    ui->setupUi(this);

    displayMode = false;
    ToggleDisplayMode();
    ui->darkModeCheckBox->setChecked(true);

    /*series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);*/

    series = new QLineSeries();
    //series->append(0, 6);
    //series->append(2, 4);

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("<Sensor Value>");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setUpdatesEnabled(true);

    //chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->verticalLayout->addWidget(chartView);
    //VBoxLayout layout = ui->tabWidget(0);

    //MQTT
    ui->telemetryDebugLabel->setStyleSheet("color: #ff0080");
    CreateMQTTClient();
    //DebugMQTT();

    //Signals
    //QObject::connect(&dlg, SIGNAL(CredentialsApplied()), this, SIGNAL(GetMQTTPlantClient())); //Connects click event of apply button to credentials applied function

    seriesToDisplay = 0;
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
        //ui->optionsMenuFrame->setVisible(false);
        //ui->optionsMenuFrame->setStyleSheet("background-color: #e0e0e0");
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
    //ui->optionsMenuFrame->setVisible(!ui->optionsMenuFrame->isVisible());
    ui->widget->setVisible(!ui->widget->isVisible());
    ui->optionsLabel->setVisible(!ui->optionsLabel->isVisible());
}

void MainWindow::on_darkModeCheckBox_released()
{
    ToggleDisplayMode();
}

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
    //Subscribe();
}

void MainWindow::CreateMQTTClient()
{
    //MQTT subscription setup
    MQTTPlantClient = new QMqttClient(this);
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not instantiate QMqttClient"));
        return;
    }
    //MQTTPlantSubscription = new QMqttSubscription();

    //Sort these credentials
    /*const QString hostname = "192.168.1.6";
    MQTTPlantClient->setHostname(hostname);

    //MQTTPlantClient->setPort(quint16(1883));
    quint16 port = 1883;
    MQTTPlantClient->setPort(port);

    const QString clientID = "qt01";
    MQTTPlantClient->setClientId(clientID);

    const QString username = "qtapp";
    MQTTPlantClient->setUsername(username);

    const QString password = "1234";
    MQTTPlantClient->setPassword(password);*/

    connect(MQTTPlantClient, &QMqttClient::stateChanged, this, &MainWindow::StateChanged);
    connect(MQTTPlantClient, &QMqttClient::disconnected, this, &MainWindow::Disconnected);
    connect(MQTTPlantClient, &QMqttClient::messageReceived, this, &MainWindow::Received);
    connect(MQTTPlantClient, &QMqttClient::pingResponseReceived, this, &MainWindow::Pinged);

    //test
    /*connect(MQTTPlantClient, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" Received Topic: ")
                                + topic.name()
                                + QLatin1String(" Message: ")
                                + message
                                + QLatin1Char('\n');
        ui->telemetryDebugLabel->setText(content);
    });
    */
    //MQTTPlantClient->connectToHost();
}

void MainWindow::Subscribe(QString topic)
{
    if (!MQTTPlantSubscription)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        //return;
    } else {
        QMessageBox::information(this, QLatin1String("Success"), QLatin1String("Successfully subscribed!"));
    }

    //Topic* pogg = new Topic();
    //topics.insert(topic, *pogg);
    //topics.emplace(topic, new Topic());

    //topics[topic] = dynamicTopic;
    //const QMqttTopicFilter* topic = new QMqttTopicFilter("chilli/light");
    //auto topic = new QMqttTopicFilter("chilli/light");

    //const QString topic = "chilli/light";

    //Dynamic version:
    //Topic dynamicTopic;
    //topics.emplace(topic, dynamicTopic);

    MQTTPlantSubscription = MQTTPlantClient->subscribe(topic, 0); //0; message loss can occur
}

void MainWindow::Unsubscribe(QString topic)
{
    if (!MQTTPlantSubscription)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not unsubscribe. Is there a valid connection?"));
        //return;
    } else {
        QMessageBox::information(this, QLatin1String("Success"), QLatin1String("Successfully unsubscribed."));
    }

    //topics.erase(topic); //dynamic version

    //const QString topic = "chilli/light";

    MQTTPlantClient->unsubscribe(topic);
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

    //QDateTime momentInTime = QDateTime::currentDateTime();
    //QDate date = QDate::currentDate();

    /*QLineSeries *series2 = new QLineSeries();
    series2->append(4, 8);
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    chart->legend()->hide();
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("<Sensor Value>");

    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);*/

    /*QLineSeries *series2 = new QLineSeries();
    series2->append(5, 10);
    chart->addSeries(series2);
    chart->createDefaultAxes();*/

    //Temporary data
    /*series = new QLineSeries();
    series->append(2, 8);
    series->append(4, 3);
    series->append(6, 7);*/

    //Formatting of data
    //quint16 extractionDeterminer = 0;

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

    ui->telemetryDebugLabel->setText((const QString)value + " " + (const QString)hours + " " + (const QString)minutes + " " + (const QString)seconds);

    //int time = hours.toInt() + minutes.toInt() + seconds.toInt();
    float valueDisplay = value.toFloat();

    QTime timeDisplay(hours.toInt(), minutes.toInt(), seconds.toInt());
    //QTime timeDisplay();

    /*
    std::vector<float> seriesValuesLight;
    std::vector<int> seriesTimesLight;

    std::vector<float> seriesValuesTemperature;
    std::vector<int> seriesTimesTemperature;

    std::vector<float> seriesValuesHumidity;
    std::vector<int> seriesTimesHumidity;

    std::vector<float> seriesValuesMoisture;
    std::vector<int> seriesTimesMoisture;
    */

    //For non-dynamic version
    //Light
    if (seriesValuesLight.size() > 63) //& by implication 'seriesTimes'
    {
        seriesValuesLight.erase(seriesValuesLight.begin(), seriesValuesLight.begin()+1);
        seriesTimesLight.erase(seriesTimesLight.begin(), seriesTimesLight.begin()+1);
    }
    seriesValuesLight.push_back(valueDisplay);
    seriesTimesLight.push_back(timeDisplay.msecsSinceStartOfDay());

    //Temperature
    if (seriesValuesTemperature.size() > 63) //& by implication 'seriesTimes'
    {
        seriesValuesTemperature.erase(seriesValuesTemperature.begin(), seriesValuesTemperature.begin()+1);
        seriesTimesTemperature.erase(seriesTimesTemperature.begin(), seriesTimesTemperature.begin()+1);
    }
    seriesValuesTemperature.push_back(valueDisplay);
    seriesTimesTemperature.push_back(timeDisplay.msecsSinceStartOfDay());

    //Humidity
    if (seriesValuesHumidity.size() > 63) //& by implication 'seriesTimes'
    {
        seriesValuesHumidity.erase(seriesValuesHumidity.begin(), seriesValuesHumidity.begin()+1);
        seriesTimesHumidity.erase(seriesTimesHumidity.begin(), seriesTimesHumidity.begin()+1);
    }
    seriesValuesHumidity.push_back(valueDisplay);
    seriesTimesHumidity.push_back(timeDisplay.msecsSinceStartOfDay());

    //Moisture
    if (seriesValuesMoisture.size() > 63) //& by implication 'seriesTimes'
    {
        seriesValuesMoisture.erase(seriesValuesMoisture.begin(), seriesValuesMoisture.begin()+1);
        seriesTimesMoisture.erase(seriesTimesMoisture.begin(), seriesTimesMoisture.begin()+1);
    }
    seriesValuesMoisture.push_back(valueDisplay);
    seriesTimesMoisture.push_back(timeDisplay.msecsSinceStartOfDay());

    RefreshGraph();

    //For dynamic version
    /*if (topics.find(topic.name()) == topics.end())
    {
        return;
    }

    //Append data
    if (topics.at(topic.name()).seriesValues.size() > 63) //& by implication 'seriesTimes'
    {
        topics.at(topic.name()).seriesValues.erase(topics.at(topic.name()).seriesValues.begin(), topics.at(topic.name()).seriesValues.begin()+1);
        topics.at(topic.name()).seriesTimes.erase(topics.at(topic.name()).seriesTimes.begin(), topics.at(topic.name()).seriesTimes.begin()+1);
    }
    topics.at(topic.name()).seriesValues.push_back(valueDisplay);
    topics.at(topic.name()).seriesTimes.push_back(timeDisplay.msecsSinceStartOfDay());

    series = new QLineSeries();
    for (int i2 = 0; i2 < topics.at(topic.name()).seriesValues.size(); i2++) //& by implication 'seriesTimes'
    {
        series->append(topics.at(topic.name()).seriesTimes[i2], topics.at(topic.name()).seriesValues[i2]);
    }*/

    /*chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->update();*/

    //series->append()
    //ui->telemetryDebugLabel->setText((const QString)message);
}

void MainWindow::Pinged()
{
    //No particular requirements
    QMessageBox::information(this, QLatin1String("Ping"), QLatin1String("Ping."));
}

void MainWindow::on_connectPlantButton_clicked()
{
//    QQuickView* popupWindow = new QQuickView();
//    popupWindow->setSource(QUrl("qrc:/connectPlantPopupWindow.qml"));
//    popupWindow->setFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    popupWindow->show();

    //CreateMQTTClient();
    //Subscribe();
    //ConnectPlantDialog dlg(this);

    if (ui->connectPlantButton->text() == "Connect Plant") //Connect to MQTT server
    {
        connectPlantDialogBox.setModal(true);
        //dlg.SetMainWindow(this);
        int result = connectPlantDialogBox.exec();
        if (result == 1)
        {
            GetMQTTPlantClient()->setHostname(connectPlantDialogBox.GetHostname());
            GetMQTTPlantClient()->setPort(connectPlantDialogBox.GetPort());
            GetMQTTPlantClient()->setClientId(connectPlantDialogBox.GetClientID());
            GetMQTTPlantClient()->setUsername(connectPlantDialogBox.GetUsername());
            GetMQTTPlantClient()->setPassword(connectPlantDialogBox.GetPassword());
            GetMQTTPlantClient()->connectToHost();
            /*Subscribe("chilli/light");
            Subscribe("chilli/temperature");
            Subscribe("chilli/humidity");
            Subscribe("chilli/moisture");*/

            //currently hardcoded; will change if dynamic
            MQTTPlantSubscription = MQTTPlantClient->subscribe((QString)"chilli/light", 0); //0; message loss can occur
            //MQTTPlantSubscription = MQTTPlantClient->subscribe((QString)"chilli/temperature", 0);
            //MQTTPlantSubscription = MQTTPlantClient->subscribe((QString)"chilli/humidity", 0);
            //MQTTPlantSubscription = MQTTPlantClient->subscribe((QString)"chilli/moisture", 0);

            ui->connectPlantButton->setText("Disconnect Plant");
        }
    }
    else //Disconnect from MQTT server
    {
        MQTTPlantClient->disconnectFromHost();
        ui->connectPlantButton->setText("Connect Plant");
    }
}

QMqttClient* MainWindow::GetMQTTPlantClient()
{
    //QMessageBox::information(this, QLatin1String("GetMQTTPlantClient()"), QLatin1String("Executed by proxy"));
    return MQTTPlantClient;
}

//Used for dynamic updating of topics
void MainWindow::on_addTopicButton_clicked()
{
    return;
    /*
    if (!MQTTPlantClient) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("No connection has been established to an MQTT server."));
        return;
    }

    addTopicDialogBox.setModal(true);
    int result = addTopicDialogBox.exec();
    if (result == 1)
    {
        if (topics.find(addTopicDialogBox.GetTopic()) != topics.end())
        {
            Unsubscribe(addTopicDialogBox.GetTopic());
            return;
        }
        Subscribe(addTopicDialogBox.GetTopic());
    }*/
}

void MainWindow::RefreshGraph()
{
    series = new QLineSeries();

    if (seriesToDisplay == 0)
    {
        for (int i2 = 0; i2 < seriesValuesLight.size(); i2++) //& by implication 'seriesTimes'
        {
            series->append(seriesTimesLight[i2], seriesValuesLight[i2]);
        }
    }
    else if (seriesToDisplay == 1)
    {
        for (int i2 = 0; i2 < seriesValuesTemperature.size(); i2++) //& by implication 'seriesTimes'
        {
            series->append(seriesTimesTemperature[i2], seriesValuesTemperature[i2]);
        }
    }
    else if (seriesToDisplay == 2)
    {
        for (int i2 = 0; i2 < seriesValuesHumidity.size(); i2++) //& by implication 'seriesTimes'
        {
            series->append(seriesTimesHumidity[i2], seriesValuesHumidity[i2]);
        }
    }
    else if (seriesToDisplay == 3)
    {
        for (int i2 = 0; i2 < seriesValuesMoisture.size(); i2++) //& by implication 'seriesTimes'
        {
            series->append(seriesTimesMoisture[i2], seriesValuesMoisture[i2]);
        }
    }

    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->update();
}

void MainWindow::on_lightButton_clicked()
{
    seriesToDisplay = 0;
    RefreshGraph();
}

void MainWindow::on_moistureButton_clicked()
{
    seriesToDisplay = 3;
    RefreshGraph();
}

void MainWindow::on_temperatureButton_clicked()
{
    seriesToDisplay = 1;
    RefreshGraph();
}

void MainWindow::on_humidityButton_clicked()
{
    seriesToDisplay = 2;
    RefreshGraph();
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

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

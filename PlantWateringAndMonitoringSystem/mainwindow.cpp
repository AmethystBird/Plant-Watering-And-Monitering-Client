#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "qlabel.h"
#include "qframe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayMode = false;
    ToggleDisplayMode();
    ui->darkModeCheckBox->setChecked(true);

    //this->setCentralWidget(ui->centralwidget->findChild<QLabel*>("titleLabel"));

    //QWidget* widget = QApplication::activeWindow();
    /*QLabel* titleLabel = widget->findChild<QLabel*>("titleLabel");
    titleLabel->setText("pogging");*/

    //this->setCentralWidget(ui->titleLabel);
    //ui->titleLabel->setStyleSheet("QLabel {color: #f0f0f0; background: #101010}");
    //QLayout* optionsMenu = widget->findChild<QLabel*>("optionsMenu");
    //this->centralWidget()->layout()->findChild<QLayout*>("optionsMenu").;
    //QFrame* optionsMenu = widget->findChild<QFrame*>("optionsMenu");
    //optionsMenu->setVisible(false);
    //this->centralWidget()->parentWidget()->findChild<QFrame*>("optionsMenu")->setVisible(false);
    //this->centralWidget()->findChild<QFrame*>("optionsMenu")->setVisible(false);
    //this->setCentralWidget(ui->centralwidget->findChild<QFrame*>("optionsMenu").setVisible(false));
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
        ui->optionsMenuFrame->setVisible(false);
        ui->optionsMenuFrame->setStyleSheet("background-color: #202020");
        ui->optionsLabel->setStyleSheet("color: #e0e0e0");
        ui->networkingLabel->setStyleSheet("color: #e0e0e0");
        ui->preferencesLabel->setStyleSheet("color: #e0e0e0");
        ui->disconnectPlantButton->setStyleSheet("color: #e0e0e0");
        ui->forgetPlantButton->setStyleSheet("color: #e0e0e0");
        ui->darkModeCheckBox->setStyleSheet("color: #e0e0e0");
        ui->hideOnCloseCheckBox->setStyleSheet("color: #e0e0e0");
        ui->sendNotificationsCheckBox->setStyleSheet("color: #e0e0e0");
    }
    else
    {
        setStyleSheet("background-color: #f0f0f0");
        ui->titleLabel->setStyleSheet("color: #101010");
        ui->optionsMenuFrame->setVisible(false);
        ui->optionsMenuFrame->setStyleSheet("background-color: #e0e0e0");
        ui->optionsLabel->setStyleSheet("color: #202020");
        ui->networkingLabel->setStyleSheet("color: #202020");
        ui->preferencesLabel->setStyleSheet("color: #202020");
        ui->disconnectPlantButton->setStyleSheet("color: #202020");
        ui->forgetPlantButton->setStyleSheet("color: #202020");
        ui->darkModeCheckBox->setStyleSheet("color: #202020");
        ui->hideOnCloseCheckBox->setStyleSheet("color: #202020");
        ui->sendNotificationsCheckBox->setStyleSheet("color: #202020");
    }
}

void MainWindow::on_optionsButton_released()
{
    ui->optionsMenuFrame->setVisible(!ui->optionsMenuFrame->isVisible());
}

void MainWindow::on_darkModeCheckBox_released()
{
    ToggleDisplayMode();
}

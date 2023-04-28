#ifndef CONNECTPLANTDIALOG_H
#define CONNECTPLANTDIALOG_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class ConnectPlantDialog;
}

class ConnectPlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectPlantDialog(QWidget *parent = nullptr);
    ~ConnectPlantDialog();

    void SetMainWindow(MainWindow* MainWindowIn);

private slots:

    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConnectPlantDialog *ui;

    MainWindow* w;
};

#endif // CONNECTPLANTDIALOG_H

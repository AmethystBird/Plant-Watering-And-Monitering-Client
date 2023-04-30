#ifndef CONNECTPLANTDIALOG_H
#define CONNECTPLANTDIALOG_H

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

    QString GetHostname();
    quint16 GetPort();
    QString GetClientID();
    QString GetUsername();
    QString GetPassword();

    Ui::ConnectPlantDialog* GetUI();

    //void SetMainWindow(MainWindow* MainWindowIn);

private slots:

    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConnectPlantDialog *ui;

    //Credentials
    QString hostname;
    quint16 port;
    QString clientID;
    QString username;
    QString password;

//signals:
    //void CredentialsApplied();
};

#endif // CONNECTPLANTDIALOG_H

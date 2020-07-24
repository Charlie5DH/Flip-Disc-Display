#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PIC_PID 0x0001
#define PIC_VID 0x7654

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <hidapi.h>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_timeout();
    void on_usbConnected();
    void on_usbDisconnected();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_checkBox_clicked(bool checked);
    void on_checkBox_a_clicked(bool checked);

    void on_checkBox_b_clicked(bool checked);

    void on_checkBox_c_clicked(bool checked);

    void on_pushButton_borrar_clicked();

private:
    Ui::MainWindow *ui;
    bool isConnected;
    bool invertido;
    QTimer timer;
    QString cartel;
    unsigned char buff[64];
    hid_device *handle;
    int i;

signals:
    void usb_connected();
    void usb_disconnected();
};

#endif // MAINWINDOW_H

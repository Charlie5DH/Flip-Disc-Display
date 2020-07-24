
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isConnected = false;

    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setMaxLength(32);
    ui->checkBox->setEnabled(false);

    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    connect(this,SIGNAL(usb_connected()),this,SLOT(on_usbConnected()));
    connect(this,SIGNAL(usb_disconnected()),this,SLOT(on_usbDisconnected()));
    timer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timeout()
{
    struct hid_device_info *devs;

    if(hid_init())
    {
        return;
    }

    devs = hid_enumerate(PIC_VID,PIC_PID);
    if(devs != NULL && isConnected == false)
    {
        isConnected = true;
        emit usb_connected();
    }

    if(devs == NULL)
    {
        emit usb_disconnected();
        isConnected = false;
    }

    hid_free_enumeration(devs);
}

void MainWindow::on_usbConnected()
{
    ui->lineEdit->setEnabled(true);
    ui->checkBox->setEnabled(true);
    ui->label_estado->setText("USB CONECTADO");
}

void MainWindow::on_usbDisconnected()
{
    ui->lineEdit->setEnabled(false);
    ui->checkBox->setEnabled(false);
    ui->label_estado->setText("USB DESCONECTADO");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    memset(buff,0x00,sizeof(buff));
    buff[0] = 0x00;
    buff[1] = arg1[arg1.length()-1].cell();

    handle = hid_open(0x7654,0x0001,NULL);
    if(!handle)
    {
        QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
        return;
    }

    i = hid_write(handle,buff,65);
    if(i<0)
        QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");

    hid_close(handle);
    hid_exit();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
        {buff[2] = 's';}
    else
        {buff[2] = 'n';}

    handle = hid_open(0x7654,0x0001,NULL);
    if(!handle)
    {
        QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
        return;
    }

    i = hid_write(handle,buff,65);
    if(i<0)
        QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");

    hid_close(handle);
    hid_exit();
}

void MainWindow::on_checkBox_a_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_b->setChecked(false);
        ui->checkBox_c->setChecked(false);
        buff[3] = 'a';
        cartel = "Message 'FACULTAD AUTOMATICA' will be shown";

        QMessageBox::information(this,"Information",cartel,QMessageBox::Ok);

        handle = hid_open(0x7654,0x0001,NULL);
        if(!handle)
        {
            QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
            return;
        }

        i = hid_write(handle,buff,65);
        if(i<0)
            QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");

        hid_close(handle);
        hid_exit();
    }


}

void MainWindow::on_checkBox_b_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_a->setChecked(false);
        ui->checkBox_c->setChecked(false);
        buff[3] = 'b';
        cartel = "Message 'BUENA SUERTE EN LOS PARCIALES' will be shown";

        QMessageBox::information(this,"Information",cartel,QMessageBox::Ok);

        handle = hid_open(0x7654,0x0001,NULL);
        if(!handle)
        {
            QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
            return;
        }

        i = hid_write(handle,buff,65);
        if(i<0)
            QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");

        hid_close(handle);
        hid_exit();
    }
}

void MainWindow::on_checkBox_c_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_b->setChecked(false);
        ui->checkBox_a->setChecked(false);
        buff[3] = 'c';
        cartel = "Message 'HAY GUARDIA' will be shown";

        QMessageBox::information(this,"Information",cartel,QMessageBox::Ok);

        handle = hid_open(0x7654,0x0001,NULL);
        if(!handle)
        {
            QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
            return;
        }

        i = hid_write(handle,buff,65);
        if(i<0)
            QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");

        hid_close(handle);
        hid_exit();
    }

}

void MainWindow::on_pushButton_borrar_clicked()
{
    buff[4] = 'z';
    ui->lineEdit->setText(" ");

    handle = hid_open(0x7654,0x0001,NULL);
    if(!handle)
    {
        QMessageBox::critical(0,"Error de comunicacion","No se pudo abrir la comunicacion con el dispositivo");
        return;
    }
    i = hid_write(handle,buff,65);
    if(i<0)
    QMessageBox::warning(0,"Error al escribir","No se pudo mandar por USB satisfactoriamente");
    hid_close(handle);
    hid_exit();
}

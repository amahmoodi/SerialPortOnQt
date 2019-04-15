#include "rfid.h"
#include "ui_rfid.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QSerialPort SerialPort;

RFID::RFID(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RFID)
{
    ui->setupUi(this);
}

RFID::~RFID()
{
    delete ui;
}

void RFID::on_Btn_Exit_clicked()
{
    this->close();
}

void RFID::on_Btn_SendData_2_clicked()
{

}

void RFID::on_Btn_Clear_clicked()
{
    ui->textEdit_ShowData->clear();
}
void MainWindow::ReadData()
    {
        QByteArray DataRead=SerialPort.readAll();
        ui->textEdit_ShowData->insertHtml("<font color=\"red\">" +DataRead + "</font>" + "\br");
    }

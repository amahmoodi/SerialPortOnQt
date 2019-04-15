#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>


QSerialPort::StopBits StopBits;
QSerialPort::BaudRate BaudRate;
QSerialPort::Parity Parity;
QSerialPort::DataBits DataBits;
QSerialPort SerialPort;
QSerialPortInfo SerialPortInfo;



#define UART_BUFFER_LEN 8
#define BUF_N 8

 char tBuf[UART_BUFFER_LEN]; //send Command or Data
 char g_ucUartRxEnd; //Receive Return data end flag
 char g_ucUartRxLen; //Receive Return data len

#define DATA_START 0xf5
#define DATA_END 0xf5
#define CMD_ENROLL1 0x01  // Add fingerprint 1st


#include <QMessageBox>
#include <QIODevice>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSerialPort *serialPort = new QSerialPort();


    serialPort = new QSerialPort(this);
    serialPort->setPortName("/dev/ttyUSB0"); //COM-port that arduino is connected to
    serialPort->open(QIODevice::ReadOnly);
    serialPort->setBaudRate(QSerialPort::Baud9600); //this is the same
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);


    if (serialPort->isOpen())
        ui->lineEdit_8->setText("Port open1");
    else

        ui->lineEdit_8->setText("Port Close");

    connect(&SerialPort,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(ui->lineEdit_5,SIGNAL(textChanged(QString)),this,SLOT(on_pushButton_Find_clicked()));



    devicedb=QSqlDatabase::addDatabase("QSQLITE");
    devicedb.setDatabaseName("//home/pi/IOdb.db");
    if(!devicedb.open())
        ui->lineEdit_6 ->setText("DataBase Close");
    else
        ui->lineEdit_6->setText("DataBase Open");







}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ReadData()
    {
       QByteArray DataRead=SerialPort.readAll();
       //ui->textEdit_ShowData_2->insertHtml("<font color=\"red\">" +DataRead + "</font>" + "\br");

       ui->textEdit_ShowData_2->setText(DataRead);
       ui->lineEdit_5->setText(DataRead);
    }


void MainWindow::on_Btn_Exit_clicked()
{
    this->close();
}






void MainWindow::on_pushButton_Save_clicked()
{
    QString name,cardno,id;
    name=ui->lineEdit_4->text();
    id =ui->lineEdit_3->text();
    cardno=ui->lineEdit_5 ->text();
    QSqlQuery query;
    query.prepare("INSERT INTO Person (id, FullName, CardNo,AccessType) "
                  "VALUES (:id, :FullName, :CardNo,:AccessType)");
    query.bindValue(":id", id);
    query.bindValue(":FullName", name);
    query.bindValue(":CardNo", cardno);
    query.bindValue(":AccessType", 1);
    query.exec();
}

void MainWindow::on_pushButton_Find_clicked()
{
    QString cardnumber,prsonid;
    QDateTime eventdatetime;
    QDateTime Currentdt;
    Currentdt=QDateTime::currentDateTime();
    cardnumber=ui->lineEdit_5->text();
    prsonid=ui->lineEdit_4->text();
    if(!devicedb.open())
    {
        qDebug()<<"Failed to open Database" ;
        return;
    }
    QSqlQuery qry;
    QSqlQuery query;
    query.exec("SELECT FullName, CardNo FROM Person WHERE CardNo='"+cardnumber+"'");
    if(qry.exec("select * from Person where CardNo='"+cardnumber+"'" ) )
    {
        int count=0;
        while (qry.next() ) {
            count++;
        }
        if (count==1) {
            ui->lineEdit_6->setText("User is exist.");
            while (query.next()) {
                 QString name = query.value(0).toString();
                 QString CardNo = query.value(1).toString();
                 qDebug() << name << CardNo;
                    ui->lineEdit_4 ->setText(name);
                    ui->lineEdit_3->setText(CardNo);
                    ui->lineEdit_7->setText(Currentdt.toString());
                    {
                        QSqlQuery query;
                        query.prepare("INSERT INTO RecordLog (id, Personid, Cardno,DateTime) "
                                      "VALUES (:id, :Personid, :Cardno,:DateTime)");
                        query.bindValue(":id", prsonid);
                        query.bindValue(":Personid", prsonid);
                        query.bindValue(":Cardno", cardnumber);
                        query.bindValue(":DateTime", Currentdt);
                        query.exec();
                    }
             }
            ui->lineEdit_5->text().clear();
        }
        else
        {
             ui->lineEdit_6->setText("User is not exist.");
        }
    }
    ui->lineEdit_5->text().clear();
}

void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    if(ui->lineEdit_5 ->text().length()>9 )
    {
         QMessageBox::information(this,"ok","readCompelete");
    }
}



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_Cmb_ComPort_activated(const QString &arg1);

    void on_Btn_Refresh_clicked();

    void ShowDetail(QString Name);


    void ReadData();




    void SendPackage(unsigned char wLen,unsigned char *ptr);

    void EnrollStep1(unsigned int u_id);

    unsigned char CmdCheckSum(unsigned char wLen,unsigned char *ptr);

    unsigned char Enroll(unsigned int UserID);

    void on_Btn_Exit_clicked();

    void on_Btn_RFID_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Find_clicked();

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_5_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase devicedb;
};

#endif // MAINWINDOW_H

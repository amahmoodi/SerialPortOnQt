#ifndef RFID_H
#define RFID_H

#include <QWidget>

namespace Ui {
class RFID;
}

class RFID : public QWidget
{
    Q_OBJECT

public:
    explicit RFID(QWidget *parent = nullptr);
    ~RFID();

private slots:
    void on_Btn_Exit_clicked();

    void on_Btn_SendData_2_clicked();

    void on_Btn_Clear_clicked();

private:
    Ui::RFID *ui;
};

#endif // RFID_H

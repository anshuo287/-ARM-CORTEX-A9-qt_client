#ifndef LOG_REG_H
#define LOG_REG_H

#include <QWidget>
#include"widget.h"
namespace Ui {
class log_reg;
}

class log_reg : public QWidget
{
    Q_OBJECT

public:
    explicit log_reg(QWidget *parent = nullptr);
    ~log_reg();


private slots:

    void on_log_pbn_clicked();


    void on_link_pbn_clicked();

    void on_reg_pbn_clicked();
private:
    Ui::log_reg *ui;
    Widget * chat_window= new Widget();
    QTcpSocket *client=new QTcpSocket;
    QHostAddress host;
    int stat;//1表示端口寻找阶段 2表示数据传送阶段  其他值全部异常
    QString port_;
    QByteArray data_in,data_out;
    QString msg;
    QString usrname="";
    void sd_usps();
};

#endif // LOG_REG_H

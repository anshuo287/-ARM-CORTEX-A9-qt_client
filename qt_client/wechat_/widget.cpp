#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include <QTextCursor>
#include <QScrollBar>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),stat(0),data(QString(""))
{
    ui->setupUi(this);
    ui->information_field->setReadOnly(true);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::logscs(QString ip, QString port)
{
    ui->ip_inform->setText(ip+":");
    ui->port_inform->setText(port);
}

void Widget::cl()
{
    ui->send_field->clear();
    ui->information_field->clear();
}

void Widget::show_s(QString x)
{
    ui->information_field->append(x+"\n");
}

void Widget::setusr(QString x)
{
    ui->current_user->setText(x);
}



void Widget::on_send_pbn_clicked()
{
    data.clear();
    data=ui->send_field->toPlainText();
    ui->send_field->clear();
    stat=1;
    emit note_cli();
}

void Widget::on_clear_pbn_clicked()
{
    ui->send_field->clear();
}

void Widget::on_leave_pbn_clicked()
{
    stat=2;
    emit note_cli();
    //qApp->quit();
}

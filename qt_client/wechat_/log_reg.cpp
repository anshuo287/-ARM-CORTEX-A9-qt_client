#include "log_reg.h"
#include "ui_log_reg.h"

log_reg::log_reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::log_reg)
{
    ui->setupUi(this);
    ui->ip_line->setText("192.168.43.5");
    stat=0;
    connect(client,&QTcpSocket::readyRead,[=]{
        if(stat==1){
            QString tmp=client->readAll();
            ui->port_num->setText("端口:"+tmp);
            port_=tmp;
            client->close();
            client->connectToHost(host,port_.toInt());
            stat=2;
            ui->link_state->setText("已连接");
        }else if(stat==2){
            QString tmp=client->readAll();
            qDebug()<<tmp<<'\n';
            if(tmp=="1111"){
                //登陆成功
                this->hide();
                usrname=ui->username_line->text();
                this->chat_window->show();
                chat_window->setusr("当前用户："+usrname);
                qDebug()<<QString("当前用户：")+usrname<<'\n';
                chat_window->logscs(host.toString(),port_);
            }else if(tmp=="333"){
                ui->log_or_reg_inform->setText("密码错误！");
            }else if(tmp=="222"){
                ui->log_or_reg_inform->setText("该用户不存在！");
            }else if(tmp=="111"){
                ui->log_or_reg_inform->setText("用户名或密码为空");
            }else if(tmp=="111111"){
                //注册成功
                ui->log_or_reg_inform->setText("用户注册成功！");
            }else if(tmp=="33333"){
                ui->log_or_reg_inform->setText("数据库错误");
            }else if(tmp=="22222"){
                ui->log_or_reg_inform->setText("该用户已经存在");
            }else if(tmp=="11111"){
                ui->log_or_reg_inform->setText("用户名或密码为空或超出长度限制");
            }else{
                chat_window->show_s(tmp);

            }
        }
    });
    connect(chat_window,&Widget::note_cli,[=]{
        qDebug()<<"rec!"<<' '<<chat_window->stat<<' '<<chat_window->data.length()<<'\n';
        if(chat_window->stat==1){
            //输出
            data_out.clear();
            QString x=usrname+":"+(chat_window->data);
            data_out=x.toUtf8();
            chat_window->show_s(x);
            client->write(data_out);
        }else if(chat_window->stat==2){
            //离开聊天室回到登录注册页面
            client->write((usrname+QString(":leave")).toUtf8());
            qDebug()<<"leave!"<<'\n';
            client->disconnectFromHost();
            ui->link_state->setText("未连接！");
            ui->port_num->setText("端口:");
            this->show();
            chat_window->cl();
            chat_window->hide();
        }
    });
}
void log_reg::sd_usps(){
    msg+=ui->username_line->text()+" "+ui->password_line->text();
}
log_reg::~log_reg()
{
    delete ui;
}


void log_reg::on_log_pbn_clicked()
{
    msg.clear();
    msg+="log ";
    sd_usps();
    qDebug()<<"开始登录"<<'\n';
    client->write(msg.toUtf8());
}

void log_reg::on_reg_pbn_clicked()
{
    msg.clear();
    msg+="reg ";
    sd_usps();
    qDebug()<<"开始注册"<<'\n';
    client->write(msg.toUtf8());
}

void log_reg::on_link_pbn_clicked()
{
     host=QHostAddress(ui->ip_line->text());
     stat=1;
     client->connectToHost(host,8000);
}


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT


private slots:
    void on_send_pbn_clicked();
    void on_clear_pbn_clicked();

    void on_leave_pbn_clicked();

signals:
    void note_cli();
private:
    Ui::Widget *ui;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void logscs(QString ip,QString port);
    void cl();
    void show_s(QString x);
    void setusr(QString x);
    int stat;
    QString data;
};
#endif // WIDGET_H

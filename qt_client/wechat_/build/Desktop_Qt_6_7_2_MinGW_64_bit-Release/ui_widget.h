/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFrame *frame_2;
    QLabel *current_user;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *connection_state;
    QLabel *ip_inform;
    QLabel *port_inform;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *send_pbn;
    QPushButton *clear_pbn;
    QPushButton *leave_pbn;
    QTextEdit *information_field;
    QTextEdit *send_field;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(888, 581);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/rsc/head.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Widget->setWindowIcon(icon);
        frame_2 = new QFrame(Widget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 20, 881, 641));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        current_user = new QLabel(frame_2);
        current_user->setObjectName("current_user");
        current_user->setGeometry(QRect(10, 330, 531, 41));
        horizontalLayoutWidget_2 = new QWidget(frame_2);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 520, 711, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        connection_state = new QLabel(horizontalLayoutWidget_2);
        connection_state->setObjectName("connection_state");

        horizontalLayout_2->addWidget(connection_state);

        ip_inform = new QLabel(horizontalLayoutWidget_2);
        ip_inform->setObjectName("ip_inform");

        horizontalLayout_2->addWidget(ip_inform);

        port_inform = new QLabel(horizontalLayoutWidget_2);
        port_inform->setObjectName("port_inform");

        horizontalLayout_2->addWidget(port_inform);

        horizontalLayoutWidget = new QWidget(frame_2);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(390, 460, 491, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        send_pbn = new QPushButton(horizontalLayoutWidget);
        send_pbn->setObjectName("send_pbn");

        horizontalLayout->addWidget(send_pbn);

        clear_pbn = new QPushButton(horizontalLayoutWidget);
        clear_pbn->setObjectName("clear_pbn");

        horizontalLayout->addWidget(clear_pbn);

        leave_pbn = new QPushButton(horizontalLayoutWidget);
        leave_pbn->setObjectName("leave_pbn");

        horizontalLayout->addWidget(leave_pbn);

        information_field = new QTextEdit(frame_2);
        information_field->setObjectName("information_field");
        information_field->setGeometry(QRect(10, 0, 871, 321));
        send_field = new QTextEdit(frame_2);
        send_field->setObjectName("send_field");
        send_field->setGeometry(QRect(10, 370, 871, 101));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\350\201\212\345\244\251\345\256\244\357\274\210\345\260\217\347\213\220\347\213\270\347\211\271\344\276\233\347\211\210\357\274\211", nullptr));
        current_user->setText(QString());
        connection_state->setText(QCoreApplication::translate("Widget", "\345\267\262\350\277\236\346\216\245\345\210\260\346\234\215\345\212\241\345\231\250\357\274\232", nullptr));
        ip_inform->setText(QString());
        port_inform->setText(QString());
        send_pbn->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        clear_pbn->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        leave_pbn->setText(QCoreApplication::translate("Widget", "\347\246\273\345\274\200\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

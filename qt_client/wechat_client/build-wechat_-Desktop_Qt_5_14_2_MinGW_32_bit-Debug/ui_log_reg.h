/********************************************************************************
** Form generated from reading UI file 'log_reg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_REG_H
#define UI_LOG_REG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_log_reg
{
public:
    QFrame *frame;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *log_pbn;
    QPushButton *reg_pbn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *link_pbn;
    QLineEdit *ip_line;
    QLabel *port_num;
    QLabel *log_or_reg_inform;
    QLabel *port_name;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *username;
    QLineEdit *username_line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *password;
    QLineEdit *password_line;
    QLabel *link_state;

    void setupUi(QWidget *log_reg)
    {
        if (log_reg->objectName().isEmpty())
            log_reg->setObjectName(QString::fromUtf8("log_reg"));
        log_reg->resize(566, 407);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/rsc/head.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        log_reg->setWindowIcon(icon);
        frame = new QFrame(log_reg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-10, 0, 581, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_4 = new QWidget(frame);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(80, 110, 411, 131));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        log_pbn = new QPushButton(verticalLayoutWidget_4);
        log_pbn->setObjectName(QString::fromUtf8("log_pbn"));

        horizontalLayout->addWidget(log_pbn);

        reg_pbn = new QPushButton(verticalLayoutWidget_4);
        reg_pbn->setObjectName(QString::fromUtf8("reg_pbn"));

        horizontalLayout->addWidget(reg_pbn);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        link_pbn = new QPushButton(verticalLayoutWidget_4);
        link_pbn->setObjectName(QString::fromUtf8("link_pbn"));

        horizontalLayout_3->addWidget(link_pbn);

        ip_line = new QLineEdit(verticalLayoutWidget_4);
        ip_line->setObjectName(QString::fromUtf8("ip_line"));

        horizontalLayout_3->addWidget(ip_line);


        verticalLayout_4->addLayout(horizontalLayout_3);

        port_num = new QLabel(frame);
        port_num->setObjectName(QString::fromUtf8("port_num"));
        port_num->setGeometry(QRect(440, 240, 51, 31));
        log_or_reg_inform = new QLabel(frame);
        log_or_reg_inform->setObjectName(QString::fromUtf8("log_or_reg_inform"));
        log_or_reg_inform->setGeometry(QRect(140, 240, 171, 31));
        port_name = new QLabel(frame);
        port_name->setObjectName(QString::fromUtf8("port_name"));
        port_name->setGeometry(QRect(380, 240, 51, 31));
        verticalLayoutWidget_5 = new QWidget(frame);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(80, 40, 411, 71));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        username = new QLabel(verticalLayoutWidget_5);
        username->setObjectName(QString::fromUtf8("username"));

        horizontalLayout_4->addWidget(username);

        username_line = new QLineEdit(verticalLayoutWidget_5);
        username_line->setObjectName(QString::fromUtf8("username_line"));

        horizontalLayout_4->addWidget(username_line);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        password = new QLabel(verticalLayoutWidget_5);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout_5->addWidget(password);

        password_line = new QLineEdit(verticalLayoutWidget_5);
        password_line->setObjectName(QString::fromUtf8("password_line"));

        horizontalLayout_5->addWidget(password_line);


        verticalLayout_5->addLayout(horizontalLayout_5);

        link_state = new QLabel(frame);
        link_state->setObjectName(QString::fromUtf8("link_state"));
        link_state->setGeometry(QRect(80, 240, 61, 31));
        link_state->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(0, 0, 255);"));

        retranslateUi(log_reg);

        QMetaObject::connectSlotsByName(log_reg);
    } // setupUi

    void retranslateUi(QWidget *log_reg)
    {
        log_reg->setWindowTitle(QCoreApplication::translate("log_reg", "\347\231\273\351\231\206\347\225\214\351\235\242", nullptr));
        log_pbn->setText(QCoreApplication::translate("log_reg", "\347\231\273\345\275\225", nullptr));
        reg_pbn->setText(QCoreApplication::translate("log_reg", "\346\263\250\345\206\214", nullptr));
        link_pbn->setText(QCoreApplication::translate("log_reg", "\350\277\236\346\216\245", nullptr));
        ip_line->setPlaceholderText(QCoreApplication::translate("log_reg", "\350\257\267\350\276\223\345\205\245\350\246\201\351\223\276\346\216\245\347\232\204\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200", nullptr));
        port_num->setText(QCoreApplication::translate("log_reg", "1", nullptr));
        log_or_reg_inform->setText(QString());
        port_name->setText(QCoreApplication::translate("log_reg", "\347\253\257\345\217\243\357\274\232", nullptr));
        username->setText(QCoreApplication::translate("log_reg", " username:", nullptr));
        password->setText(QCoreApplication::translate("log_reg", " password:", nullptr));
        link_state->setText(QCoreApplication::translate("log_reg", "\346\234\252\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class log_reg: public Ui_log_reg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_REG_H

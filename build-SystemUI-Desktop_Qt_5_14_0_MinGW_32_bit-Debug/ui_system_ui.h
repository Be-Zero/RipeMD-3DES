/********************************************************************************
** Form generated from reading UI file 'system_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEM_UI_H
#define UI_SYSTEM_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_System_UI
{
public:
    QWidget *centralwidget;
    QPushButton *Select;
    QTextEdit *FilePath;
    QTextEdit *KeyValue;
    QComboBox *LineBox;
    QPushButton *Encryption;
    QPushButton *Decryption;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *Save;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *System_UI)
    {
        if (System_UI->objectName().isEmpty())
            System_UI->setObjectName(QString::fromUtf8("System_UI"));
        System_UI->resize(522, 314);
        centralwidget = new QWidget(System_UI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Select = new QPushButton(centralwidget);
        Select->setObjectName(QString::fromUtf8("Select"));
        Select->setGeometry(QRect(390, 50, 101, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        Select->setFont(font);
        FilePath = new QTextEdit(centralwidget);
        FilePath->setObjectName(QString::fromUtf8("FilePath"));
        FilePath->setGeometry(QRect(30, 50, 331, 31));
        KeyValue = new QTextEdit(centralwidget);
        KeyValue->setObjectName(QString::fromUtf8("KeyValue"));
        KeyValue->setGeometry(QRect(30, 130, 331, 31));
        LineBox = new QComboBox(centralwidget);
        LineBox->addItem(QString());
        LineBox->addItem(QString());
        LineBox->addItem(QString());
        LineBox->addItem(QString());
        LineBox->addItem(QString());
        LineBox->addItem(QString());
        LineBox->setObjectName(QString::fromUtf8("LineBox"));
        LineBox->setGeometry(QRect(330, 180, 61, 31));
        LineBox->setFont(font);
        LineBox->setLayoutDirection(Qt::LeftToRight);
        LineBox->setEditable(false);
        LineBox->setFrame(true);
        LineBox->setModelColumn(0);
        Encryption = new QPushButton(centralwidget);
        Encryption->setObjectName(QString::fromUtf8("Encryption"));
        Encryption->setGeometry(QRect(80, 230, 121, 31));
        Encryption->setFont(font);
        Decryption = new QPushButton(centralwidget);
        Decryption->setObjectName(QString::fromUtf8("Decryption"));
        Decryption->setGeometry(QRect(320, 230, 121, 31));
        Decryption->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 281, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 90, 281, 31));
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 180, 171, 31));
        label_3->setFont(font1);
        Save = new QPushButton(centralwidget);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(390, 130, 101, 31));
        Save->setFont(font);
        System_UI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(System_UI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 522, 22));
        System_UI->setMenuBar(menubar);
        statusbar = new QStatusBar(System_UI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        System_UI->setStatusBar(statusbar);

        retranslateUi(System_UI);

        LineBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(System_UI);
    } // setupUi

    void retranslateUi(QMainWindow *System_UI)
    {
        System_UI->setWindowTitle(QCoreApplication::translate("System_UI", "System_UI", nullptr));
        Select->setText(QCoreApplication::translate("System_UI", "Select", nullptr));
        FilePath->setHtml(QCoreApplication::translate("System_UI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", nullptr));
        KeyValue->setHtml(QCoreApplication::translate("System_UI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", nullptr));
        LineBox->setItemText(0, QCoreApplication::translate("System_UI", "ECB", nullptr));
        LineBox->setItemText(1, QCoreApplication::translate("System_UI", "CBC", nullptr));
        LineBox->setItemText(2, QCoreApplication::translate("System_UI", "CFB", nullptr));
        LineBox->setItemText(3, QCoreApplication::translate("System_UI", "OFB", nullptr));
        LineBox->setItemText(4, QCoreApplication::translate("System_UI", "CTR", nullptr));
        LineBox->setItemText(5, QCoreApplication::translate("System_UI", "PCBC", nullptr));

        Encryption->setText(QCoreApplication::translate("System_UI", "Encryption", nullptr));
        Decryption->setText(QCoreApplication::translate("System_UI", "Decryption", nullptr));
        label->setText(QCoreApplication::translate("System_UI", "Please input file path:", nullptr));
        label_2->setText(QCoreApplication::translate("System_UI", "Please input key:", nullptr));
        label_3->setText(QCoreApplication::translate("System_UI", "Operating Mode:", nullptr));
        Save->setText(QCoreApplication::translate("System_UI", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class System_UI: public Ui_System_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEM_UI_H

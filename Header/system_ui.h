#ifndef SYSTEM_UI_H
#define SYSTEM_UI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <string>
#include "ui_system_ui.h"
#include "OPMode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class System_UI; }
QT_END_NAMESPACE

class System_UI : public QMainWindow
{
    Q_OBJECT

public:
    System_UI(QWidget *parent = nullptr);
    ~System_UI();

private slots:
    void on_Select_clicked();

    void on_Encryption_clicked();

    void on_Decryption_clicked();

    void on_Save_clicked();

private:
    Ui::System_UI *ui;
    QString filepath;
    // "../test/test.txt";
    // "../test/test_En.txt";
    QString userkey; // = "qth";
    int mode;
};
#endif // SYSTEM_UI_H

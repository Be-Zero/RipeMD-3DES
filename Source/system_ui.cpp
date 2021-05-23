#include "../Header/system_ui.h"

System_UI::System_UI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::System_UI)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("RipeMD-TripleDes");
    ui->OpenDirectory->setDisabled(true);
    ui->Encryption->setDisabled(true);
    ui->Decryption->setDisabled(true);
}

System_UI::~System_UI() {
    delete ui;
}

void System_UI::on_Select_clicked() {
    filepath = QFileDialog::getOpenFileName(this, tr("File dialog"), tr("../test/"));
    ui->FilePath->setStyleSheet("background:#FFFFFF; font-size:16px");
    ui->FilePath->setText(filepath);

    QFileInfo fileinfo(filepath);
    if(fileinfo.exists() && fileinfo.isFile()) {
        ui->statusbar->showMessage(filepath);
        ui->OpenDirectory->setDisabled(false);
    } else {
        ui->FilePath->setStyleSheet("background:#ff0000");
        ui->statusbar->showMessage("Invalid file path !");
        ui->Encryption->setDisabled(true);
        ui->Decryption->setDisabled(true);
    }
}

void System_UI::on_Save_clicked() {
    ui->KeyValue->setStyleSheet("background:#FFFFFF; font-size:16px");
    userkey = ui->KeyValue->toPlainText();
    ui->KeyValue->setText(userkey);

    if(userkey!="") {
        ui->statusbar->showMessage("You can start encryption and decryption !");
        ui->Encryption->setDisabled(false);
        ui->Decryption->setDisabled(false);
    } else {
        ui->KeyValue->setStyleSheet("background:#ff0000");
        ui->statusbar->showMessage("Invalid user key !");
        ui->Encryption->setDisabled(true);
        ui->Decryption->setDisabled(true);
    }
}

void System_UI::on_Encryption_clicked() {
    ui->statusbar->showMessage("busying...");
    QApplication::processEvents();
    mode = ui->LineBox->currentIndex();
    string pstr = filepath.toStdString();
    string kstr = userkey.toStdString();
    OPMode ep(&pstr[0], &kstr[0], true);
    clock_t time = clock();
    switch(mode) {
        case 0: {
            ep.ECB();
            break;
        }
        case 1: {
            ep.CBC();
            break;
        }
        case 2: {
            ep.CFB();
            break;
        }
        case 3: {
            ep.OFB();
            break;
        }
        case 4: {
            ep.CTR();
            break;
        }
        case 5: {
            ep.PCBC();
            break;
        }
    }
    char *TimeStr = new char[30];
    sprintf(TimeStr,"Encryption succeeded ! time consuming : %lf s !",(clock()-time)*1.0/CLOCKS_PER_SEC);
    ui->statusbar->showMessage(TimeStr);
    delete[] TimeStr;
    string suffix = pstr.substr(pstr.find_last_of('.') + 1);
    string name = pstr.substr(0, pstr.rfind("."));
    pstr = name + "_En." + suffix;
    filepath =  QString::fromStdString(pstr);
    ui->FilePath->setStyleSheet("background:#FFFFFF; font-size:16px");
    ui->FilePath->setText(filepath);
}

void System_UI::on_Decryption_clicked() {
    clock_t time = clock();
    ui->statusbar->showMessage("busying...");
    QApplication::processEvents();
    mode = ui->LineBox->currentIndex();
    string pstr = filepath.toStdString();
    string kstr = userkey.toStdString();
    OPMode ep(&pstr[0], &kstr[0], false);
    switch(mode) {
        case 0: {
            ep.ECB();
            break;
        }
        case 1: {
            ep.CBC();
            break;
        }
        case 2: {
            ep.CFB();
            break;
        }
        case 3: {
            ep.OFB();
            break;
        }
        case 4: {
            ep.CTR();
            break;
        }
        case 5: {
            ep.PCBC();
            break;
        }
    }
    char *TimeStr = new char[30];
    sprintf(TimeStr,"Decryption succeeded ! time consuming : %lf s !",(clock()-time)*1.0/CLOCKS_PER_SEC);
    ui->statusbar->showMessage(TimeStr);
    delete[] TimeStr;
    string suffix = pstr.substr(pstr.find_last_of('.') + 1);
    string name = pstr.substr(0, pstr.rfind("_"));
    pstr = name + "." + suffix;
    filepath =  QString::fromStdString(pstr);
    ui->FilePath->setStyleSheet("background:#FFFFFF; font-size:16px");
    ui->FilePath->setText(filepath);
}



void System_UI::on_OpenDirectory_clicked()
{
    string tmp = filepath.toStdString();
    tmp = tmp.substr(0, tmp.rfind("/"));
    QDesktopServices::openUrl(QUrl(QString::fromStdString(tmp), QUrl::TolerantMode));
}

#include "../Header/system_ui.h"

System_UI::System_UI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::System_UI)
{
    ui->setupUi(this);

    ui->Encryption->setDisabled(true);
    ui->Decryption->setDisabled(true);
}

System_UI::~System_UI() {
    delete ui;
}

void System_UI::on_Select_clicked() {
    filepath = QFileDialog::getOpenFileName(this, tr("文件对话框"), tr("."));
    ui->FilePath->setStyleSheet("background:#FFFFFF");
    ui->FilePath->setText(filepath);

    QFileInfo fileinfo(filepath);
    if(fileinfo.exists() && fileinfo.isFile()) {
        ui->statusbar->showMessage(filepath);
        ui->Encryption->setDisabled(false);
        ui->Decryption->setDisabled(false);
    } else {
        ui->FilePath->setStyleSheet("background:#ff0000");
        ui->statusbar->showMessage("无效的文件路径！");
    }
}

void System_UI::on_Save_clicked() {
    userkey = ui->KeyValue->toPlainText();
    ui->KeyValue->setText(userkey);
}

void System_UI::on_Encryption_clicked() {
    mode = ui->LineBox->currentIndex();
    string pstr = filepath.toStdString(), kstr = userkey.toStdString();
    OPMode ep(pstr, kstr, 1);
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
}

void System_UI::on_Decryption_clicked() {
    mode = ui->LineBox->currentIndex();
    string pstr = filepath.toStdString(), kstr = userkey.toStdString();
    OPMode ep(pstr, kstr, 0);
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
}



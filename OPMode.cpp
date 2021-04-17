//
// Created by 12036 on 2021/4/17.
//

#include "OPMode.h"

OPMode::OPMode(string Path, string Key, bool E_D) {
    FilaPath = Path;
    Key = UserKey;
    flag = E_D;
}

void OPMode::ECB() {
    Key key(UserKey);
    if (flag) {
        File_IO file_En(FilaPath);
        file_En.Operation(1, key);
    } else {
        File_IO file_DE(FilaPath);
        file_DE.Operation(0, key);
    }
}

void OPMode::CBC() {

}

void OPMode::CFB() {

}

void OPMode::OFB() {

}

void OPMode::CTR() {

}
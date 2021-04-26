//
// Created by 12036 on 2021/4/17.
//

#include "../Header/OPMode.h"

OPMode::OPMode(char *Path, char *key, bool E_D) {
    UserKey = key;
    FilaPath = Path;
    flag = E_D;
    memcpy(InitialVector, "Be_Zero!", 8);
}

void OPMode::ECB() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            des.Operation(Plaintext + i, 1);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            des.Operation(Plaintext + i, 0);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::CBC() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            Xor(Plaintext + i, InitialVector);
            des.Operation(Plaintext + i, 1);
            memcpy(InitialVector, Plaintext + i, 8);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        char tmp[8];
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            memcpy(tmp, Plaintext + i, 8);
            des.Operation(Plaintext + i, 0);
            Xor(Plaintext + i, InitialVector);
            memcpy(InitialVector, tmp, 8);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::CFB() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            Xor(Plaintext + i, InitialVector);
            memcpy(InitialVector, Plaintext + i, 8);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        char tmp[8];
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            memcpy(tmp, Plaintext + i, 8);
            Xor(Plaintext + i, InitialVector);
            memcpy(InitialVector, tmp, 8);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::OFB() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            Xor(Plaintext + i, InitialVector);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            Xor(Plaintext + i, InitialVector);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::CTR() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);
    char tmp[1];

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            Xor(Plaintext + i, InitialVector);
            memcpy(tmp, InitialVector, 1);
            memcpy(InitialVector, InitialVector + 1, 7);
            memcpy(InitialVector + 7, tmp, 1);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            des.Operation(InitialVector, 1);
            Xor(Plaintext + i, InitialVector);
            memcpy(tmp, InitialVector, 1);
            memcpy(InitialVector, InitialVector + 1, 7);
            memcpy(InitialVector + 7, tmp, 1);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::PCBC() {
    Key key(UserKey);
    key.MakeSubKey();
    File_IO file_io(FilaPath);
    char tmp[8];

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < file_io.GetEnFileSize(); i += 8) {
            memcpy(tmp, Plaintext + i, 8);
            Xor(Plaintext + i, InitialVector);
            des.Operation(Plaintext + i, 1);
            memcpy(InitialVector, tmp, 8);
            Xor(InitialVector, Plaintext + i);
        }
        file_io.Save_EN(Plaintext);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < file_io.GetDeFileSize(); i += 8) {
            memcpy(tmp, Plaintext + i, 8);
            des.Operation(Plaintext + i, 0);
            Xor(Plaintext + i, InitialVector);
            memcpy(InitialVector, tmp, 8);
            Xor(InitialVector, Plaintext + i);
        }
        file_io.Save_DE(Plaintext);
    }
    cout << "finished!" << endl;
}

void OPMode::Xor(char *left, char *right) { // 异或操作
    for (int i = 0; i < 8; ++i)
        left[i] ^= right[i];
}

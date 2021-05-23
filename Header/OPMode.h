//
// Created by 12036 on 2021/4/17.
//

#ifndef RIPEMD_3DES_OPMODE_H
#define RIPEMD_3DES_OPMODE_H

#include "File_IO.h"

using namespace std;

class OPMode {
private:
    char *Plaintext;

    char *UserKey;

    bool flag;

    char InitialVector[8];

    char *FilaPath;

    TripleDes des;

public:
    OPMode(char *Path, char *UserKey, bool E_D);

    void ECB();

    void CBC();

    void CFB();

    void OFB();

    void CTR();

    void PCBC();

    void Xor(char *left, char *right);
};

#endif //RIPEMD_3DES_OPMODE_H

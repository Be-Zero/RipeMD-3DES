//
// Created by 12036 on 2021/4/17.
//

#ifndef RIPEMD_3DES_OPMODE_H
#define RIPEMD_3DES_OPMODE_H

#include "File_IO.h"

using namespace std;

#endif //RIPEMD_3DES_OPMODE_H

class OPMode {
private:
    char *Plaintext;

    char *res;

    char *FilaPath;

    char *UserKey;

    char *UserSubKey;

    bool flag;

    char *InitialVector;

public:
    OPMode(char *Path, char *Key, bool E_D);

    void ECB();

    void CBC();

    void CFB();

    void OFB();

    void CTR();

    void PCBC();

    string StringToBits(string s);

    bitset<64> OpPlus (bitset<64> a, bitset<64> b);

    void Xor(char *left, char *right);
};
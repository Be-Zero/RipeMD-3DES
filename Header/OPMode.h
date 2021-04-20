//
// Created by 12036 on 2021/4/17.
//

#ifndef RIPEMD_3DES_OPMODE_H
#define RIPEMD_3DES_OPMODE_H

#include <string>
#include "File_IO.h"

using namespace std;

#endif //RIPEMD_3DES_OPMODE_H

class OPMode {
private:
    string Plaintext;

    string res;

    string FilaPath;

    string UserKey;

    bool flag;

    string InitialVector;

public:
    OPMode(string Path, string Key, bool E_D);

    void ECB();

    void CBC();

    void CFB();

    void OFB();

    void CTR();

    void PCBC();

    string StringToBits(string s);

    bitset<64> OpPlus (bitset<64> a, bitset<64> b);
};
//
// Created by 12036 on 2021/4/16.
//

#ifndef RIPEMD_3DES_RIPEMD_256_H
#define RIPEMD_3DES_RIPEMD_256_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <iostream>

using namespace std;

#endif //RIPEMD_3DES_RIPEMD_256_H

typedef unsigned char byte;
typedef unsigned long ulong;

class RipeMD_256 {
private:
    ulong RMDSize;

public:
    RipeMD_256();

    void MDinit(ulong MDbuf[]); // 初始化

    ulong BytesToUlong(byte *strptr); // 转换

    void compress(ulong *MDbuf, ulong *X);

    ulong F(ulong x, ulong y, ulong z);

    ulong G(ulong x, ulong y, ulong z);

    ulong H(ulong x, ulong y, ulong z);

    ulong I(ulong x, ulong y, ulong z);

    ulong ROL(ulong x, ulong n);

    void FF(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void GG(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void HH(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void II(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void FFF(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void GGG(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void HHH(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void III(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s);

    void MDfinish(ulong *MDbuf, byte *strptr, ulong lswlen, ulong mswlen);

    string RMD(byte *message);
};
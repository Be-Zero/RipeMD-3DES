//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

TripleDes::TripleDes() {
    Li = BitsText;
    Ri = BitsText + 32;
}

void TripleDes::DES(int flag, bool Type) {
    for (int i = 0; i < 64; ++i)
        buffer[i] = BitsText[Table_IP[i] - 1];
    memcpy(BitsText, buffer, 64);
    if (Type == true) //加密
        for (int i = 0; i < 16; ++i) { // 16轮操作
            memcpy(temp, Ri, 32);
            funF(Ri, Key::SubKey[flag][i]);
            for (int j = 0; j < 32; ++j)
                Ri[j] ^= Li[j];
            memcpy(Li, temp, 32);
        }
    else //解密
        for (int i = 15; i >= 0; --i) {// 加密操作的拟操作
            memcpy(temp, Li, 32);
            funF(Li, Key::SubKey[flag][i]);
            for (int j = 0; j < 32; ++j)
                Li[j] ^= Ri[j];
            memcpy(Ri, temp, 32);
        }
    for (int i = 0; i < 64; ++i)
        buffer[i] = BitsText[Table_InverseIP[i] - 1];
    memcpy(BitsText, buffer, 64);
}

void TripleDes::funF(bool *In, const bool *Ki) { // F函数
    for (int i = 0; i < 48; ++i)
        buffer[i] = In[Table_E[i] - 1];
    memcpy(MR, buffer, 48);
    for (int i = 0; i < 48; ++i)
        MR[i] ^= Ki[i];
    funS(In, MR); // S盒
    for (int i = 0; i < 32; ++i)
        buffer[i] = In[Table_P[i] - 1];
    memcpy(In, buffer, 32);
}

void TripleDes::funS(bool *Out, const bool *In) { // S盒置换
    for (int i = 0, j, k; i < 8; ++i, In += 6, Out += 4) {
        j = (In[0] << 1) + In[5];
        k = (In[1] << 3) + (In[2] << 2) + (In[3] << 1) + In[4];
        Byte2Bit(Out, &Box_S[i][j][k], 4);
    }
}

//字节转换成位
void TripleDes::Byte2Bit(bool *Out, const char *In, int bits) {
    for (int i = 0; i < bits; ++i)
        Out[i] = (In[i >> 3] >> (i & 7)) & 1;
}

//位转换字节
void TripleDes::Bit2Byte() {
    int bits = 64;
    memset(Plaintext, 0, bits >> 3);
    for (int i = 0; i < bits; ++i)
        Plaintext[i >> 3] |= BitsText[i] << (i & 7);
}

void TripleDes::Operation(char *T, bool flag) {
    Plaintext = T;
    Byte2Bit(BitsText, Plaintext, 64);
    if (flag) {
        DES(0, ENCRYPT);
        DES(1, !ENCRYPT);
        DES(0, ENCRYPT);
    } else {
        DES(0, DECRYPT);
        DES(1, !DECRYPT);
        DES(0, DECRYPT);
    }
    Bit2Byte();
}
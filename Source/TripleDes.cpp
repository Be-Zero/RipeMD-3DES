//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

TripleDes::TripleDes() {
    Li = BitsText;
    Ri = BitsText + 32;
}

void TripleDes::DES(int flag, bool Type) {
    Byte2Bit(BitsText, Plaintext, 64);
    Transform(BitsText, BitsText, Table_IP, 64); // 将明文转换为64位
    if (Type == true) //加密
        for (int i = 0; i < 16; ++i) {// 16轮操作
            memcpy(temp, Ri, 32);
            funF(Ri, SubKey + flag * 16 * 48 + i * 16);
            Xor(Ri, Li, 32);
            memcpy(Li, temp, 32);
        }
    else //解密
        for (int i = 15; i >= 0; --i) {// 加密操作的拟操作
            memcpy(temp, Li, 32);
            funF(Li, SubKey + flag * 16 * 48 + i * 16);
            Xor(Li, Ri, 32);
            memcpy(Ri, temp, 32);
        }
    Transform(BitsText, BitsText, Table_InverseIP, 64); // 转换为64位
    Bit2Byte(Plaintext, BitsText, 64);
}

void TripleDes::Transform(bool *Out, bool *In, const char *Table, int len) { // 置换函数
    for (int i = 0; i < len; ++i) {
        buffer[i] = In[Table[i] - 1];
    }
    memcpy(Out, buffer, len);
}

void TripleDes::Xor(bool *left, const bool *right, int len) { // 异或操作
    for (int i = 0; i < len; ++i)
        left[i] ^= right[i];
}

void TripleDes::funF(bool In[32], const bool *Ki) { // F函数
    Transform(MR, In, Table_E, 48); // 转化为48位
    Xor(MR, Ki, 48); // 异或操作
    funS(In, MR); // S盒
    Transform(In, In, Table_P, 32); // 转化为32位
}

void TripleDes::funS(bool Out[32], const bool In[48]) { // S盒置换
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
void TripleDes::Bit2Byte(char *Out, const bool *In, int bits) {
    memset(Plaintext, 0, bits >> 3);
    for (int i = 0; i < bits; ++i) {
        Plaintext[i >> 3] |= BitsText[i] << (i & 7);
    }
}

void TripleDes::Operation(bool *key, char *T, bool flag) {
    Plaintext = T;
    SubKey = key;
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
}
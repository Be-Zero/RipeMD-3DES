//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

TripleDes::TripleDes() {
    buffer = new char[64];
}

void TripleDes::GetBitsText(char *T) {
    BitsText = T;
}

void TripleDes::DES(char *key, int flag, bool Type) {
    Transform(BitsText, Table_IP, 64); // 将明文转换为64位

    if (Type == ENCRYPT) //加密
        for (int i = 0; i < 16; ++i) {// 16轮操作
            strncpy(buffer, BitsText + 32, 32);
            funF(&key[flag * 16 * 48 + i * 16]);
            Xor(BitsText, 32);
            strncpy(BitsText, BitsText + 32, 32);
            strncpy(BitsText + 32, buffer, 32);
        }
    else //解密
        for (int i = 15; i >= 0; --i) {// 加密操作的拟操作
            strncpy(buffer, BitsText, 32);
            funF(&key[flag * 16 * 48 + i * 16]);
            Xor(BitsText + 32, 32);
            strncpy(BitsText + 32, BitsText, 32);
            strncpy(BitsText, buffer, 32);
        }
    Transform(BitsText, Table_InverseIP, 64); // 转换为64位
}

void TripleDes::Transform(char *In, const char *Table, int len) { // 置换函数
    for (int i = 0; i < len; ++i)
        buffer[i] = In[Table[i] - 1];
    strncpy(In, buffer, len);
}

void TripleDes::Xor(char *right, int len) { // 异或操作
    for (int i = 0; i < len; ++i)
        if (buffer[i] == right[i])
            buffer[i] = '0';
        else buffer[i] = '1';
}

void TripleDes::funF(char *key) { // F函数
    Transform(buffer, Table_E, 48); // 转化为48位
    Xor(key, 48); // 异或操作
    funS(); // S盒
    Transform(buffer, Table_P, 32); // 转化为32位
}

void TripleDes::funS() { // S盒置换
    for (int i = 0; i < 8; ++i) {
        char *flag = buffer + i * 6;

        int row = 0, column = 0;
        if (flag[0] == '1')
            row += 2;
        if (flag[5] == '1')
            row++;
        if (flag[1] == '1')
            column += 8;
        if (flag[2] == '1')
            column += 4;
        if (flag[3] == '1')
            column += 2;
        if (flag[4] == '1')
            column++;

        bitset<4> tmp = Box_S[i][row][column];
        strncpy(buffer + i * 4, tmp.to_string().c_str(), 4);
    }
}

char *TripleDes::Operation(char *key, char *T, bool flag) {
    GetBitsText(T);

    if (flag) {
        DES(key, 0, ENCRYPT);
        DES(key, 1, !ENCRYPT);
        DES(key, 0, ENCRYPT);
    } else {
        DES(key, 0, DECRYPT);
        DES(key, 1, !DECRYPT);
        DES(key, 0, DECRYPT);
    }
    return BitsText;
}

TripleDes::~TripleDes() {
    delete[] buffer;
}
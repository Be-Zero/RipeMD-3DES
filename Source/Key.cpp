//
// Created by BeZero on 2021/4/12.
//

#include "../Header/Key.h"

Key::Key(char *In) {
    UserKey = In;
}

void Key::RipeMD_process() {
    RipeMD_256 ep;
    UserBitKey = ep.RMD((byte *) UserKey);
}

void Key::Transform(char *Out, const string &In, const char *Table, int len) { // 将64位密钥压缩位56位
    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];
}

void Key::MakeSubKey() { // 生成子密钥
    RipeMD_process();

    char *KL1 = new char[56];
    char *KL2;
    char *KR1 = new char[56];
    char *KR2;
    Transform(KL1, UserBitKey.substr(0, 64), Table_PC1, 56);
    KL2 = KL1 + 28;
    Transform(KR1, UserBitKey.substr(64, 64), Table_PC1, 56);
    KR2 = KR1 + 28;

    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL1, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        MoveLeft(KR1, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        char *tmp = new char[56];
        strncpy(tmp, KL1, 28);
        strncpy(tmp + 28, KR1, 28);
        Transform((char *) SubKey + i * 16, tmp, Table_PC2, 48); // 存入相应的子密钥中
        delete[] tmp;
        tmp = nullptr;
    }

    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL2, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        MoveLeft(KR2, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        char *tmp = new char[56];
        strncpy(tmp, KL2, 28);
        strncpy(tmp + 28, KR2, 28);
        Transform((char *) SubKey + 16 * 48 + i * 16, tmp, Table_PC2, 48); // 存入相应的子密钥中
        delete[] tmp;
        tmp = nullptr;
    }
}

void Key::MoveLeft(char *T, int flag) { // 循环移位
    char *tmp = new char[flag];
    strncpy(tmp, T, flag);
    strncpy(T, T + flag, 28 - flag);
    strncpy(T + 28 - flag, tmp, flag);
    delete[] tmp;
    tmp = NULL;
}

char *Key::GetSubKey() { // 获取子密钥
    return (char *) SubKey;
}
//
// Created by BeZero on 2021/4/12.
//

#include "../Header/Key.h"

Key::Key(string &In) {
    UserKey = In;
}

void Key::RipeMD_process() {
    RipeMD_256 ep;
    UserBitKey = ep.RMD((byte*)UserKey.c_str());
}

string Key::Transform(const string &In, const char *Table, int len) { // 将64位密钥压缩位56位
    string Out = In;

    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];

    return Out.substr(0, len);
}

void Key::MakeSubKey() { // 生成子密钥
    RipeMD_process();

    string KL1 = Transform(UserBitKey.substr(0, 64), Table_PC1, 56).substr(0, 28), KR1 = Transform(UserBitKey.substr(0, 64), Table_PC1, 56).substr(28, 28);
    string KL2 = Transform(UserBitKey.substr(64, 64), Table_PC1, 56).substr(0, 28), KR2 = Transform(UserBitKey.substr(64, 64), Table_PC1, 56).substr(28, 28);

    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL1, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        MoveLeft(KR1, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        SubKey[0][i] = Transform(KL1 + KR1, Table_PC2, 48); // 存入相应的子密钥中
    }

    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL2, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        MoveLeft(KR2, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        SubKey[1][i] = Transform(KL2 + KR2, Table_PC2, 48); // 存入相应的子密钥中
    }
}

void Key::MoveLeft(string &T, int flag) { // 循环移位
    T = T.substr(flag) + T.substr(0, flag);
}

string Key::GetSubKey(int num, int round) { // 获取子密钥
    return SubKey[num][round];
}
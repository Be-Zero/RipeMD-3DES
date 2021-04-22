//
// Created by BeZero on 2021/4/12.
//

#include "../Header/Key.h"

Key::Key(char *In) {
    UserKey = In;
    KL = K;
    KR = K + 28;
}

void Key::RipeMD_process() {
    RipeMD_256 ep;
    UserKey = (char*)ep.RMD((unsigned char *) UserKey);
}

void Key::Transform(bool *Out, bool *In, const char *Table, int len) { // 置换函数
    for (int i = 0; i < len; ++i)
        buffer[i] = In[Table[i] - 1];
    memcpy(Out, buffer, len);
}

void Key::MakeSubKey() { // 生成子密钥
    RipeMD_process();

    Byte2Bit(K, UserKey, 64);
    Transform(K, K, Table_PC1, 56);
    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL, 28, Table_Moveleft[i]);
        MoveLeft(KR, 28, Table_Moveleft[i]);
        Transform(SubKey[0][i], K, Table_PC2, 48);
    }

    Byte2Bit(K, UserKey + 8, 64);
    Transform(K, K, Table_PC1, 56);
    for (int i = 0; i < 16; ++i) {
        MoveLeft(KL, 28, Table_Moveleft[i]);
        MoveLeft(KR, 28, Table_Moveleft[i]);
        Transform(SubKey[1][i], K, Table_PC2, 48);
    }
}

void Key::MoveLeft(bool *In, int len, int loop) {
    memcpy(buffer, In, loop);
    memcpy(In, In + loop, len - loop);
    memcpy(In + len - loop, buffer, loop);
}

bool *Key::GetSubKey() { // 获取子密钥
    return (bool *) SubKey;
}

void Key::Byte2Bit(bool *Out, const char *In, int bits) {
    for (int i = 0; i < bits; ++i)
        Out[i] = (In[i >> 3] >> (i & 7)) & 1;
}
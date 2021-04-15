//
// Created by BeZero on 2021/4/12.
//

#include "Key.h"

Key::Key(string In) {
    UserKey = In;
}

void Key::RipeMD_process() { // TODO RipeMD
    UserBitKey = StringToBits(UserKey);
}

string Key::Transform(const string In, const char *Table, int len) { // 将64位密钥压缩位56位
    string Out = In;

    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];

    return Out.substr(0, len);
}

void Key::MakeSubKey() { // 生成子密钥
    RipeMD_process();
    string tmp = UserBitKey;

    InitialReplacement1 = Transform(tmp.substr(0, 64), Table_PC1, 56);
    InitialReplacement2 = Transform(tmp.substr(64, 64), Table_PC1, 56);

    string KL1 = InitialReplacement1.substr(0, 28), KR1 = InitialReplacement1.substr(28, 28);
    string KL2 = InitialReplacement2.substr(0, 28), KR2 = InitialReplacement2.substr(28, 28);

    for (int i = 0; i < 16; ++i) {
        KL1 = MoveLeft(KL1, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        KR1 = MoveLeft(KR1, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        SubKey[0][i] = Transform(KL1 + KR1, Table_PC2, 48); // 存入相应的子密钥中
    }

    for (int i = 0; i < 16; ++i) {
        KL2 = MoveLeft(KL2, Table_Moveleft[i]); // 循环左移，处理子密钥的左半部分
        KR2 = MoveLeft(KR2, Table_Moveleft[i]); // 同上，处理子密钥的右半部分
        SubKey[1][i] = Transform(KL2 + KR2, Table_PC2, 48); // 存入相应的子密钥中
    }
}

string Key::MoveLeft(string T, int flag) { // 循环移位
    return T.substr(flag) + T.substr(0, flag);
}

string Key::GetSubKey(int num, int round) { // 获取子密钥
    return SubKey[num][round];
}

string Key::StringToBits(string s) { // 字符串转二进制串
    string ans = "";
    for (int i = 0; i < s.size(); ++i) {
        bitset<8> tmp = s[i];
        ans += tmp.to_string();
    }
    return ans;
}
//
// Created by BeZero on 2021/4/3.
//

#ifndef SECURITYSYSTEM_KEY_H
#define SECURITYSYSTEM_KEY_H

#include <string>
#include <bitset>
#include "RipeMD_256.h"

using namespace std;

#endif //SECURITYSYSTEM_KEY_H

class Key {
private:
    string UserKey; // 用户密钥1和2

    string UserBitKey; // 用户密钥经过RipeMD处理后的结果

    string SubKey[2][16]; // 轮密钥

    constexpr static char Table_PC1[56] = { // 密钥初始置换表
            57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
    };

    constexpr static char Table_Moveleft[16] = { // 左移运算表
            1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
    };

    constexpr static char Table_PC2[48] = { // 密钥压缩置换
            14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };
public:
    Key(string &In); // 构造函数

    void RipeMD_process(); // TODO RipeMD

    string Transform(const string &In, const char *Table, int len); // 将64位密钥压缩位56位

    void MakeSubKey(); // 生成子密钥

    void MoveLeft(string &T, int flag); // 循环移位

    string GetSubKey(int num, int round); // 获取子密钥
};


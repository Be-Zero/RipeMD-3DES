//
// Created by 12036 on 2021/4/14.
//

#ifndef SECURITYSYSTEM_FILE_IO_H
#define SECURITYSYSTEM_FILE_IO_H

#include <iostream>
#include <string>
#include <string.h>
#include <bitset>
#include <fstream>
#include "Key.h"
#include "TripleDes.h"

using namespace std;

#endif //SECURITYSYSTEM_FILE_IO_H
class File_IO {
private:
    string FilePath; // 文件路径
    int FileSize; // 文件大小
    int BlockNum; // 文件块数
    string Plaintext; // 存储明文
    string FileBits; // 文件内容
    int Supple; // 末块补充长度

public:
    File_IO(string In); // 构造函数
    void Load_EN(); // 读取文件
    void Save_EN(); // 存储文件
    void Load_DE(); // 读取文件
    void Save_DE(); // 存储文件
    void Operation(bool flag, Key key); // 运行
};
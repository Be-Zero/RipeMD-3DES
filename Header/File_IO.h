//
// Created by 12036 on 2021/4/14.
//

#ifndef SECURITYSYSTEM_FILE_IO_H
#define SECURITYSYSTEM_FILE_IO_H

#include <iostream>
#include <string.h>
#include <bitset>
#include <fstream>
#include "TripleDes.h"

using namespace std;

class File_IO {
private:
    string FilePath; // 文件路径
    int FileSize; // 文件大小
    int BlockNum; // 文件块数
    char *Plaintext; // 存储明文
    int Supple; // 末块补充长度

public:
    File_IO(string In); // 构造函数
    ~File_IO();
    char* Load_EN(); // 读取文件
    void Save_EN(char *In); // 存储文件
    char* Load_DE(); // 读取文件
    void Save_DE(char *In); // 存储文件
    int GetEnFileSize();
    int GetDeFileSize();
};

#endif //SECURITYSYSTEM_FILE_IO_H
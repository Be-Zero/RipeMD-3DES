//
// Created by 12036 on 2021/4/14.
//

#include "File_IO.h"

File_IO::File_IO(string In) {
    FilePath = In;
}

void File_IO::Load_EN() {
    ifstream file(FilePath, ios::in | ios::binary | ios::ate); // 以二进制读取文件，并将当前指针位置指向文件末尾
    FileSize = file.tellg(); // 返回当前位置的长度，表示文件大小
    BlockNum = (FileSize + 7) / 8; // 需要加密的块数
    Supple = BlockNum * 8 - FileSize; // 填充的二进制位长度
    file.seekg(0, ios::beg); // 将文件指针位置指向文件开始处
    char *buffer = new char[FileSize + 1]; // 初始化明文指针
    file.read(buffer, FileSize); // 读取全部文件
    Plaintext = buffer; // 记录文件内容
    for (int i = 0; i < Supple; ++i) // 填充
        Plaintext += "0";
    delete (buffer); // 释放指针
    file.close(); // 关闭文件
}

void File_IO::Save_EN() {
    char *buffer = new char[BlockNum * 8];
    strcpy(buffer, Plaintext.c_str());
    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("."));
    ofstream file(name + "_En." + suffix, ios::binary);
    file.write(buffer, BlockNum * 8);
    delete (buffer);

    buffer = new char[32];
    bitset<32> b = Supple;
    strcpy(buffer, b.to_string().c_str());
    file.write(buffer, 32);
    delete (buffer);

    file.close();
}

void File_IO::Load_DE() {
    ifstream file(FilePath, ios::in | ios::binary | ios::ate); // 以二进制读取文件，并将当前指针位置指向文件末尾
    FileSize = file.tellg(); // 返回当前位置的字节数，表示文件大小

    BlockNum = (FileSize - 32) / 8; // 需要解密的块数
    file.seekg(0, ios::beg); // 将文件指针位置指向文件开始处
    char *buffer = new char[FileSize + 1]; // 初始化明文指针
    file.read(buffer, FileSize); // 读取全部文件
    buffer[FileSize + 1] = '\n';
    Plaintext = buffer; // 记录文件内容
    delete (buffer);

    FileSize -= 32;
    bitset<32> b(Plaintext.substr(FileSize, 32));
    Plaintext = Plaintext.substr(0, FileSize);
    Supple = b.to_ulong();
    FileSize -= Supple;
    file.close(); // 关闭文件
}

void File_IO::Save_DE() {
    char *buffer = new char[FileSize];
    strcpy(buffer, Plaintext.substr(0, FileSize).c_str());
    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("_"));
    ofstream file(name + "_De." + suffix, ios::binary);
    file.write(buffer, FileSize);
    delete (buffer);
    file.close();
}

void File_IO::Operation(bool flag, Key key) {
    TripleDes des;
    if (flag) {
        Load_EN();
        Plaintext = des.Operation(key, Plaintext, flag);
        Save_EN();
    } else {
        Load_DE();
        Plaintext = des.Operation(key, Plaintext, flag);
        Save_DE();
    }
}
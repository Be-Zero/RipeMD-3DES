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
    char *buffer = new char[BlockNum * 8]; // 初始化明文指针
    file.read(buffer, FileSize); // 读取全部文件
    FileBits = buffer; // 记录文件内容
    cout<<"***"<<FileBits<<endl;
    for (int i = 0; i < Supple; ++i) // 填充
        FileBits += "0";

    delete (buffer); // 释放指针
    file.close(); // 关闭文件
}

void File_IO::Save_EN() {
    char *buffer = new char[BlockNum * 8];
    strcpy(buffer, FileBits.c_str());

    ofstream file(FilePath + "se", ios::binary);
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
    char *buffer = new char[BlockNum * 8]; // 初始化明文指针
    file.read(buffer, FileSize); // 读取全部文件
    FileBits = buffer; // 记录文件内容
    delete (buffer);

    FileSize -= 32;
    bitset<32> b(FileBits.substr(FileSize, 32));
    FileBits = FileBits.substr(0, FileSize);
    Supple = b.to_ulong();
    FileSize -= Supple;
    file.close(); // 关闭文件
}

void File_IO::Save_DE() {
    char *buffer = new char[FileSize];
    strcpy(buffer, FileBits.substr(0, FileSize).c_str());

    ofstream file(FilePath.substr(0, FilePath.size() - 2) + "cp", ios::binary);
    file.write(buffer, FileSize);
    delete (buffer);
    file.close();
}

void File_IO::Operation(bool flag, Key key) {
    TripleDes des;
    if (flag) {
        Load_EN();
        des.Operation(key, FileBits, flag);
        Save_EN();
    } else {
        Load_DE();
        des.Operation(key, FileBits, flag);
        Save_DE();
    }
}
//
// Created by BeZero on 2021/4/14.
//

#include "../Header/File_IO.h"

File_IO::File_IO(string In) {
    FilePath = In;
}

char *File_IO::Load_EN() {
    ifstream file(FilePath, ios::in | ios::binary | ios::ate); // 以二进制读取文件，并将当前指针位置指向文件末尾
    FileSize = file.tellg(); // 返回当前位置的长度，表示文件大小

    BlockNum = (FileSize + 7) / 8; // 需要加密的块数

    Supple = BlockNum * 8 - FileSize; // 填充的二进制位长度

    file.seekg(0, ios::beg); // 将文件指针位置指向文件开始处
    Plaintext = new char[FileSize + Supple]; // 初始化明文指针
    file.read(Plaintext, FileSize); // 读取全部文件

    for (int i = 0; i < Supple; ++i) // 填充
        Plaintext[FileSize + i] = '0';

    file.close(); // 关闭文件

    return Plaintext;
}

void File_IO::Save_EN(char *In) {
    Plaintext = In;

    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("."));
    ofstream file(name + "_En." + suffix, ios::binary);
    file.write(Plaintext, BlockNum * 8);

    char buffer[32];
    bitset<32> b = Supple;

    memcpy(buffer, b.to_string().c_str(), 32);
    file.write(buffer, 32);
}

char* File_IO::Load_DE() {
    ifstream file(FilePath, ios::in | ios::binary | ios::ate); // 以二进制读取文件，并将当前指针位置指向文件末尾
    FileSize = file.tellg(); // 返回当前位置的字节数，表示文件大小

    file.seekg(0, ios::beg); // 将文件指针位置指向文件开始处
    Plaintext = new char[FileSize]; // 初始化明文指针
    file.read(Plaintext, FileSize); // 读取全部文件

    FileSize -= 32;
    char buffer[32];
    memcpy(buffer, Plaintext + FileSize, 32);
    bitset<32> b(buffer);
    Supple = b.to_ulong();

    file.close(); // 关闭文件
    return Plaintext;
}

void File_IO::Save_DE(char *In) {
    Plaintext = In;
    FileSize -= Supple;

    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("_"));
    ofstream file(name + "_De." + suffix, ios::binary);
    file.write(Plaintext, FileSize);
    file.close();
}

int File_IO::GetEnFileSize() {
    return BlockNum * 8;
}

int File_IO::GetDeFileSize() {
    return FileSize;
}

File_IO::~File_IO() {
    delete[] Plaintext;
}

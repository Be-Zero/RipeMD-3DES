//
// Created by BeZero on 2021/4/14.
//

#include "../Header/File_IO.h"

File_IO::File_IO(string In) {
    FilePath = In;
}

string File_IO::Load_EN() {
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
    BitStr = StringToBits(FileSize + Supple);

    delete Plaintext;
    return BitStr;
}

void File_IO::Save_EN(string &In) {
    BitStr = In;

    RestorePlaintext();

    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("."));
    ofstream file(name + "_En." + suffix, ios::binary);
    file.write(Plaintext, BlockNum * 8);

    char *buffer = new char[32];
    bitset<32> b = Supple;
    strcpy(buffer, b.to_string().c_str());
    file.write(buffer, 32);
    delete (buffer);
    delete Plaintext;
    file.close();
}

string File_IO::Load_DE() {
    ifstream file(FilePath, ios::in | ios::binary | ios::ate); // 以二进制读取文件，并将当前指针位置指向文件末尾
    FileSize = file.tellg(); // 返回当前位置的字节数，表示文件大小

    file.seekg(0, ios::beg); // 将文件指针位置指向文件开始处
    Plaintext = new char[FileSize]; // 初始化明文指针
    file.read(Plaintext, FileSize); // 读取全部文件

    FileSize -= 32;
    char *buffer = new char[32];
    strncpy(buffer, Plaintext + FileSize, 32);
    bitset<32> b(buffer);
    Supple = b.to_ulong();
    delete buffer;

    BitStr = StringToBits(FileSize); // 936

    FileSize -= Supple;

    file.close(); // 关闭文件
    return BitStr;
}

void File_IO::Save_DE(string &In) {
    BitStr = In;

    RestorePlaintext();

    string suffix = FilePath.substr(FilePath.find_last_of('.') + 1);
    string name = FilePath.substr(0, FilePath.rfind("_"));
    ofstream file(name + "_De." + suffix, ios::binary);
    file.write(Plaintext, FileSize);
    file.close();
    delete Plaintext;
}

string File_IO::StringToBits(int size) { // 字符串转二进制串
    string ans = "";
    for (int i = 0; i < size; ++i) {
        bitset<8> tmp = Plaintext[i];
        ans += tmp.to_string();
    }
    return ans;
}

void File_IO::RestorePlaintext() { // 将二进制信息转化为字节
    Plaintext = new char[BitStr.size() / 8];

    for (int i = 0; i < BitStr.size(); i += 8) {
        bitset<8> tmp(BitStr.substr(i, 8));
        char ans = tmp.to_ulong();

        Plaintext[i / 8] = ans;
    }
}
//
// Created by BeZero on 2021/4/12.
//

#include "TripleDes.h"

void TripleDes::GetBitsText(string T) { // TODO 获取明文
    BitsText = StringToBits(T);
}

void TripleDes::DES(Key key, int flag, bool Type) {
    BitsBlocks = Transform(BitsBlocks, Table_IP, 64); // 将明文转换为64位

    if (Type == ENCRYPT) //加密
        for (int i = 0; i < 16; ++i) // 16轮操作
            BitsBlocks = BitsBlocks.substr(32, 32) + Xor32(funF(BitsBlocks.substr(32, 32), key.GetSubKey(flag, i)),
                                                           BitsBlocks.substr(0, 32)); // 异或操作
    else //解密
        for (int i = 15; i >= 0; --i) // 加密操作的拟操作
            BitsBlocks = Xor32(funF(BitsBlocks.substr(0, 32), key.GetSubKey(flag, i)), BitsBlocks.substr(32, 32)) +
                         BitsBlocks.substr(0, 32); // 异或操作

    BitsBlocks = Transform(BitsBlocks, Table_InverseIP, 64); // 转换为64位
}

string TripleDes::Transform(const string In, const char *Table, int len) { // 置换函数
    string Out = "0000000000000000000000000000000000000000000000000000000000000000";

    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];

    return Out.substr(0, len);
}

string TripleDes::Xor32(string left, string right) { // 异或操作
    bitset<32> x(left), y(right);
    return (x ^ y).to_string();
}

string TripleDes::Xor48(string left, string right) { // 异或操作
    bitset<48> x(left), y(right);

    return (x ^ y).to_string();
}

string TripleDes::funF(string T, string key) { // F函数
    string Tmp = T;

    Tmp = Transform(Tmp, Table_E, 48); // 转化为48位
    Tmp = Xor48(Tmp, key); // 异或操作
    Tmp = funS(Tmp); // S盒

    return Transform(Tmp, Table_P, 32); // 转化为32位
}

string TripleDes::funS(const string Tmp) { // S盒置换
    string ans = "";
    for (int i = 0; i < 8; ++i) {
        string flag = Tmp.substr(i * 6, 6);
        bitset<2> row(flag.substr(0, 1) + flag.substr(5, 1));
        bitset<4> column(flag.substr(1, 4));
        column = Box_S[i][row.to_ulong()][column.to_ulong()];
        ans += column.to_string();
    }

    return ans;
}

string TripleDes::StringToBits(string s) { // 字符串转二进制串
    string ans = "";
    for (int i = 0; i < s.size(); ++i) {
        bitset<8> tmp = s[i];
        ans += tmp.to_string();
    }
    return ans;
}

string TripleDes::RestorePlaintext() { // 将二进制信息转化为字节
    string res = "";

    for (int i = 0; i < BitsText.size(); i += 8) {
        bitset<8> tmp(BitsText.substr(i, 8));
        char ans = tmp.to_ulong();
        res += "0";
        res[res.size() - 1] = ans;
    }
    return res;
}

string TripleDes::Operation(Key key, string Text, bool flag) {
    key.MakeSubKey();
    GetBitsText(Text);

    if (flag) {
        for (int i = 0; i < BitsText.size(); i += 64) {
            BitsBlocks = BitsText.substr(i, 64);

            DES(key, 0, ENCRYPT);
            DES(key, 1, !ENCRYPT);
            DES(key, 0, ENCRYPT);

            BitsText = BitsText.substr(0, i) + BitsBlocks + BitsText.substr(i + 64);
        }
        cout << "ENCRYPT success!" << endl;
    } else {
        for (int i = 0; i < BitsText.size(); i += 64) {
            BitsBlocks = BitsText.substr(i, 64);

            DES(key, 0, DECRYPT);
            DES(key, 1, !DECRYPT);
            DES(key, 0, DECRYPT);

            BitsText = BitsText.substr(0, i) + BitsBlocks + BitsText.substr(i + 64);
        }
        cout << "DECRYPT success!" << endl;
    }
    return RestorePlaintext();
}
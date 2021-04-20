//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

void TripleDes::GetBitsText(string T) {
    BitsText = T;
}

void TripleDes::DES(Key key, int flag, bool Type) {
    BitsText = Transform(BitsText, Table_IP, 64); // 将明文转换为64位

    if (Type == ENCRYPT) //加密
        for (int i = 0; i < 16; ++i) // 16轮操作
            BitsText = BitsText.substr(32, 32) + Xor32(funF(BitsText.substr(32, 32), key.GetSubKey(flag, i)),
                                                       BitsText.substr(0, 32)); // 异或操作
    else //解密
        for (int i = 15; i >= 0; --i) // 加密操作的拟操作
            BitsText = Xor32(funF(BitsText.substr(0, 32), key.GetSubKey(flag, i)), BitsText.substr(32, 32)) +
                    BitsText.substr(0, 32); // 异或操作

    BitsText = Transform(BitsText, Table_InverseIP, 64); // 转换为64位
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

string TripleDes::Operation(Key key, string Text, bool flag) {
    GetBitsText(Text);

    if (flag) {
            DES(key, 0, ENCRYPT);
            DES(key, 1, !ENCRYPT);
            DES(key, 0, ENCRYPT);
    } else {
            DES(key, 0, DECRYPT);
            DES(key, 1, !DECRYPT);
            DES(key, 0, DECRYPT);
    }
    return BitsText;
}
//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

void TripleDes::GetBitsText(char *T) {
    char *s = new char[65];
    strncpy(s, T, 64);
    s[64]='/0';
    BitsText = s;
}

void TripleDes::DES(Key key, int flag, bool Type) {
    Transform(BitsText, Table_IP, 64); // 将明文转换为64位

    if (Type == ENCRYPT) //加密
        for (int i = 0; i < 16; ++i) // 16轮操作
            BitsText = BitsText.substr(32, 32) + Xor(funF(BitsText.substr(32, 32), key.GetSubKey(flag, i)),
                    BitsText.substr(0, 32), 32); // 异或操作
    else //解密
        for (int i = 15; i >= 0; --i) // 加密操作的拟操作
            BitsText = Xor(funF(BitsText.substr(0, 32), key.GetSubKey(flag, i)), BitsText.substr(32, 32), 32) +
                    BitsText.substr(0, 32); // 异或操作

    Transform(BitsText, Table_InverseIP, 64); // 转换为64位
}

void TripleDes::Transform(string &In, const char *Table, int len) { // 置换函数
    string Out = "0000000000000000000000000000000000000000000000000000000000000000";

    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];

    In = Out.substr(0, len);
}

string TripleDes::Xor(string left, string right, int len) { // 异或操作
    string res=left;
    for(int i=0;i<len;++i)
        if(left[i]==right[i])
            res[i]='0';
        else res[i]='1';
    return res;
}

string TripleDes::funF(string T, string key) { // F函数
    string Tmp = T;
    Transform(Tmp, Table_E, 48); // 转化为48位
    Tmp = Xor(Tmp, key, 48); // 异或操作
    Tmp = funS(Tmp); // S盒
    Transform(Tmp, Table_P, 32); // 转化为32位
    return  Tmp;
}

string TripleDes::funS(const string &Tmp) { // S盒置换
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

string TripleDes::Operation(Key key, char *p, bool flag) {
    GetBitsText(p);

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
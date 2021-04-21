//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

void TripleDes::GetBitsText(char *T) {
    BitsText = new char[64];
    strncpy(BitsText, T, 64);
}

void TripleDes::DES(Key key, int flag, bool Type) {
    Transform(BitsText, Table_IP, 64); // 将明文转换为64位

    if (Type == ENCRYPT) //加密
        for (int i = 0; i < 16; ++i) {// 16轮操作
            char *In = new char[48];
            strncpy(In, BitsText + 32, 32);
            funF(In, BitsText + 32, key.GetSubKey(flag, i));
            Xor(In, In, BitsText, 32);
            strncpy(BitsText, BitsText + 32, 32);
            strncpy(BitsText + 32, In, 32);
            delete In;
            In = NULL;
        }
    else //解密
        for (int i = 15; i >= 0; --i) {// 加密操作的拟操作
            char *In = new char[48];
            strncpy(In, BitsText, 32);
            funF(In, BitsText, key.GetSubKey(flag, i));
            Xor(In, In, BitsText + 32, 32);
            strncpy(BitsText + 32, BitsText, 32);
            strncpy(BitsText, In, 32);
            delete In;
            In = NULL;
        }
    Transform(BitsText, Table_InverseIP, 64); // 转换为64位
}

void TripleDes::Transform(char *In, const char *Table, int len) { // 置换函数
    char *Out = new char[len];
    for (int i = 0; i < len; ++i)
        Out[i] = In[Table[i] - 1];
    strncpy(In, Out, len);
    delete Out;
    Out = NULL;
}

void TripleDes::Xor(char *In, char *left, string right, int len) { // 异或操作
    for(int i=0;i<len;++i)
        if(left[i]==right[i])
            In[i]='0';
        else In[i]='1';
}

void TripleDes::funF(char *In, char *T, string key) { // F函数
    Transform(In, Table_E, 48); // 转化为48位
    Xor(In, In, key, 48); // 异或操作
    funS(In); // S盒
    Transform(In, Table_P, 32); // 转化为32位
}

void TripleDes::funS(char *In) { // S盒置换
    char *ans = new char[32];
    for (int i = 0; i < 8; ++i) {
        char *flag = In + i*6;

        int row=0, column=0;
        if(flag[0]=='1')
            row +=2;
        if(flag[5]=='1')
            row++;
        if(flag[1]=='1')
            column+=8;
        if(flag[2]=='1')
            column+=4;
        if(flag[3]=='1')
            column+=2;
        if(flag[4]=='1')
            column++;

        bitset<4> tmp = Box_S[i][row][column];
        strncpy(ans + i * 4, tmp.to_string().c_str(), 4);
}
    strncpy(In, ans, 32);
    delete ans;
    ans = NULL;
}

char* TripleDes::Operation(Key key, char *T, bool flag) {
    GetBitsText(T);

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
//
// Created by BeZero on 2021/4/12.
//

#include "../Header/TripleDes.h"

TripleDes::TripleDes() {

}

void TripleDes::DES(int flag, bool Type) {
    buffer = 0;
    for (int i = 0; i < 64; ++i) {
        buffer <<= 1;

        buffer |= (BitsText >> (64 - Table_IP[i])) & LB64_MASK;
    }
    BitsText = buffer;
    Ri = (ul) (BitsText & L64_MASK);
    Li = (ul) (BitsText >> 32) & L64_MASK;

    if (Type == true) //加密
        for (int i = 0; i < 16; ++i) { // 16轮操作
            temp = Ri;
            bitset<48> bt(Key::SubKey[flag][i]);

            funF(Ri, bt.to_ullong());

            Ri ^= Li;
            Li = temp;
        }
    else //解密
        for (int i = 15; i >= 0; --i) {// 加密操作的拟操作
            temp = Li;
            bitset<48> bt(Key::SubKey[flag][i]);
            funF(Li, bt.to_ullong());
            Li ^= Ri;
            Ri = temp;
        }

    BitsText = ((ull) Li << 32) | (ull) Ri;

    buffer = 0;
    for (int i = 0; i < 64; ++i) {
        buffer <<= 1;
        buffer |= (BitsText >> (64 - Table_InverseIP[i])) & LB64_MASK;
    }
    BitsText = buffer;
}

void TripleDes::funF(ul &In, ull Ki) { // F函数
    buffer = 0;
    for (int i = 0; i < 48; ++i) {
        buffer <<= 1;
        buffer |= (ull) ((In >> (32 - Table_E[i])) & LB32_MASK);
    }

    MR = buffer ^ Ki;

    buffer = 0;
    for (int i = 0; i < 8; ++i) {
        char row = (char) ((MR & (0x0000840000000000 >> 6 * i)) >> (42 - 6 * i));
        row = (row >> 4) | (row & 0x01);
        char column = (char) ((MR & (0x0000780000000000 >> 6 * i)) >> (43 - 6 * i));
        buffer <<= 4;
        buffer |= (ul) (Box_S[i][row][column] & 0x0f);
    }

    In = buffer;

    buffer = 0;
    for (int i = 0; i < 32; ++i) {
        buffer <<= 1;
        buffer |= (ull) ((In >> (32 - Table_P[i])) & LB32_MASK);
    }
    In = buffer;
}

void TripleDes::String2Ull() {
    BitsText = 0;
    for (int i = 0; i < 8; ++i) {
        BitsText<<=8;
        BitsText |= (ull)Plaintext[i] & 0x00000000000000ff;
    }
}

void TripleDes::Ull2String() {
    for (int i = 7; i >= 0; --i) {
        Plaintext[i] = (char)(BitsText & 0xff);
        BitsText >>= 8;
    }
}

void TripleDes::Operation(char *T, bool flag) {
    Plaintext = T;

    String2Ull();

    if (flag) {
        DES(0, ENCRYPT);

        DES(1, !ENCRYPT);
        DES(0, ENCRYPT);
    } else {
        DES(0, DECRYPT);

        DES(1, !DECRYPT);
        DES(0, DECRYPT);
    }
    Ull2String();
}

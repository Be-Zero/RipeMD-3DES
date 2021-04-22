//
// Created by 12036 on 2021/4/16.
//

#include "../Header/RipeMD_256.h"

void RipeMD_256::MDinit() { // 初始化
    MDbuf[0] = 0x67452301UL;
    MDbuf[1] = 0xefcdab89UL;
    MDbuf[2] = 0x98badcfeUL;
    MDbuf[3] = 0x10325476UL;
    MDbuf[4] = 0x76543210UL;
    MDbuf[5] = 0xFEDCBA98UL;
    MDbuf[6] = 0x89ABCDEFUL;
    MDbuf[7] = 0x01234567UL;
}

ulong RipeMD_256::BytesToUlong(unsigned char *strptr) { // 每次处理四个字节，字节转ulong
    return ((ulong) *(strptr + 3) << 24) | ((ulong) *(strptr + 2) << 16) | ((ulong) *(strptr + 1) << 8) |
            ((ulong) *(strptr));
}

ulong RipeMD_256::F(ulong x, ulong y, ulong z) { // F函数
    return x ^ y ^ z;
}

ulong RipeMD_256::G(ulong x, ulong y, ulong z) { // G函数
    return (x & y) | (~x & z);
}

ulong RipeMD_256::H(ulong x, ulong y, ulong z) { // H函数
    return (x | ~y) ^ z;
}

ulong RipeMD_256::I(ulong x, ulong y, ulong z) { // I函数
    return (x & z) | (y & ~z);
}

ulong RipeMD_256::ROL(ulong x, ulong n) { //
    return (x << n) | (x >> (32 - n));
}

void RipeMD_256::FF(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // FF函数
    a += F(b, c, d) + x;
    a = ROL(a, s);
}

void RipeMD_256::GG(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // GG函数
    a += G(b, c, d) + x + 0x5a827999UL;
    a = ROL(a, s);
}

void RipeMD_256::HH(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // HH函数
    a += H(b, c, d) + x + 0x6ed9eba1UL;
    a = ROL(a, s);
}

void RipeMD_256::II(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // II函数
    a += I(b, c, d) + x + 0x8f1bbcdcUL;
    a = ROL(a, s);
}

void RipeMD_256::FFF(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // FFF函数
    a += F(b, c, d) + x;
    a = ROL(a, s);
}

void RipeMD_256::GGG(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // GGG函数
    a += G(b, c, d) + x + 0x6d703ef3UL;
    a = ROL(a, s);
}

void RipeMD_256::HHH(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // HHH函数
    a += H(b, c, d) + x + 0x5c4dd124UL;
    a = ROL(a, s);
}

void RipeMD_256::III(ulong &a, ulong b, ulong c, ulong d, ulong x, ulong s) { // III函数
    a += I(b, c, d) + x + 0x50a28be6UL;
    a = ROL(a, s);
}

void RipeMD_256::compress(ulong *X) { // 压缩函数
    ulong aa = MDbuf[0], bb = MDbuf[1], cc = MDbuf[2], dd = MDbuf[3];
    ulong aaa = MDbuf[4], bbb = MDbuf[5], ccc = MDbuf[6], ddd = MDbuf[7];
    ulong tmp;

    /* round 1 */
    FF(aa, bb, cc, dd, X[0], 11);
    FF(dd, aa, bb, cc, X[1], 14);
    FF(cc, dd, aa, bb, X[2], 15);
    FF(bb, cc, dd, aa, X[3], 12);
    FF(aa, bb, cc, dd, X[4], 5);
    FF(dd, aa, bb, cc, X[5], 8);
    FF(cc, dd, aa, bb, X[6], 7);
    FF(bb, cc, dd, aa, X[7], 9);
    FF(aa, bb, cc, dd, X[8], 11);
    FF(dd, aa, bb, cc, X[9], 13);
    FF(cc, dd, aa, bb, X[10], 14);
    FF(bb, cc, dd, aa, X[11], 15);
    FF(aa, bb, cc, dd, X[12], 6);
    FF(dd, aa, bb, cc, X[13], 7);
    FF(cc, dd, aa, bb, X[14], 9);
    FF(bb, cc, dd, aa, X[15], 8);

    /* parallel round 1 */
    III(aaa, bbb, ccc, ddd, X[5], 8);
    III(ddd, aaa, bbb, ccc, X[14], 9);
    III(ccc, ddd, aaa, bbb, X[7], 9);
    III(bbb, ccc, ddd, aaa, X[0], 11);
    III(aaa, bbb, ccc, ddd, X[9], 13);
    III(ddd, aaa, bbb, ccc, X[2], 15);
    III(ccc, ddd, aaa, bbb, X[11], 15);
    III(bbb, ccc, ddd, aaa, X[4], 5);
    III(aaa, bbb, ccc, ddd, X[13], 7);
    III(ddd, aaa, bbb, ccc, X[6], 7);
    III(ccc, ddd, aaa, bbb, X[15], 8);
    III(bbb, ccc, ddd, aaa, X[8], 11);
    III(aaa, bbb, ccc, ddd, X[1], 14);
    III(ddd, aaa, bbb, ccc, X[10], 14);
    III(ccc, ddd, aaa, bbb, X[3], 12);
    III(bbb, ccc, ddd, aaa, X[12], 6);

    tmp = aa;
    aa = aaa;
    aaa = tmp;

    /* round 2 */
    GG(aa, bb, cc, dd, X[7], 7);
    GG(dd, aa, bb, cc, X[4], 6);
    GG(cc, dd, aa, bb, X[13], 8);
    GG(bb, cc, dd, aa, X[1], 13);
    GG(aa, bb, cc, dd, X[10], 11);
    GG(dd, aa, bb, cc, X[6], 9);
    GG(cc, dd, aa, bb, X[15], 7);
    GG(bb, cc, dd, aa, X[3], 15);
    GG(aa, bb, cc, dd, X[12], 7);
    GG(dd, aa, bb, cc, X[0], 12);
    GG(cc, dd, aa, bb, X[9], 15);
    GG(bb, cc, dd, aa, X[5], 9);
    GG(aa, bb, cc, dd, X[2], 11);
    GG(dd, aa, bb, cc, X[14], 7);
    GG(cc, dd, aa, bb, X[11], 13);
    GG(bb, cc, dd, aa, X[8], 12);

    /* parallel round 2 */
    HHH(aaa, bbb, ccc, ddd, X[6], 9);
    HHH(ddd, aaa, bbb, ccc, X[11], 13);
    HHH(ccc, ddd, aaa, bbb, X[3], 15);
    HHH(bbb, ccc, ddd, aaa, X[7], 7);
    HHH(aaa, bbb, ccc, ddd, X[0], 12);
    HHH(ddd, aaa, bbb, ccc, X[13], 8);
    HHH(ccc, ddd, aaa, bbb, X[5], 9);
    HHH(bbb, ccc, ddd, aaa, X[10], 11);
    HHH(aaa, bbb, ccc, ddd, X[14], 7);
    HHH(ddd, aaa, bbb, ccc, X[15], 7);
    HHH(ccc, ddd, aaa, bbb, X[8], 12);
    HHH(bbb, ccc, ddd, aaa, X[12], 7);
    HHH(aaa, bbb, ccc, ddd, X[4], 6);
    HHH(ddd, aaa, bbb, ccc, X[9], 15);
    HHH(ccc, ddd, aaa, bbb, X[1], 13);
    HHH(bbb, ccc, ddd, aaa, X[2], 11);

    tmp = bb;
    bb = bbb;
    bbb = tmp;

    /* round 3 */
    HH(aa, bb, cc, dd, X[3], 11);
    HH(dd, aa, bb, cc, X[10], 13);
    HH(cc, dd, aa, bb, X[14], 6);
    HH(bb, cc, dd, aa, X[4], 7);
    HH(aa, bb, cc, dd, X[9], 14);
    HH(dd, aa, bb, cc, X[15], 9);
    HH(cc, dd, aa, bb, X[8], 13);
    HH(bb, cc, dd, aa, X[1], 15);
    HH(aa, bb, cc, dd, X[2], 14);
    HH(dd, aa, bb, cc, X[7], 8);
    HH(cc, dd, aa, bb, X[0], 13);
    HH(bb, cc, dd, aa, X[6], 6);
    HH(aa, bb, cc, dd, X[13], 5);
    HH(dd, aa, bb, cc, X[11], 12);
    HH(cc, dd, aa, bb, X[5], 7);
    HH(bb, cc, dd, aa, X[12], 5);

    /* parallel round 3 */
    GGG(aaa, bbb, ccc, ddd, X[15], 9);
    GGG(ddd, aaa, bbb, ccc, X[5], 7);
    GGG(ccc, ddd, aaa, bbb, X[1], 15);
    GGG(bbb, ccc, ddd, aaa, X[3], 11);
    GGG(aaa, bbb, ccc, ddd, X[7], 8);
    GGG(ddd, aaa, bbb, ccc, X[14], 6);
    GGG(ccc, ddd, aaa, bbb, X[6], 6);
    GGG(bbb, ccc, ddd, aaa, X[9], 14);
    GGG(aaa, bbb, ccc, ddd, X[11], 12);
    GGG(ddd, aaa, bbb, ccc, X[8], 13);
    GGG(ccc, ddd, aaa, bbb, X[12], 5);
    GGG(bbb, ccc, ddd, aaa, X[2], 14);
    GGG(aaa, bbb, ccc, ddd, X[10], 13);
    GGG(ddd, aaa, bbb, ccc, X[0], 13);
    GGG(ccc, ddd, aaa, bbb, X[4], 7);
    GGG(bbb, ccc, ddd, aaa, X[13], 5);

    tmp = cc;
    cc = ccc;
    ccc = tmp;

    /* round 4 */
    II(aa, bb, cc, dd, X[1], 11);
    II(dd, aa, bb, cc, X[9], 12);
    II(cc, dd, aa, bb, X[11], 14);
    II(bb, cc, dd, aa, X[10], 15);
    II(aa, bb, cc, dd, X[0], 14);
    II(dd, aa, bb, cc, X[8], 15);
    II(cc, dd, aa, bb, X[12], 9);
    II(bb, cc, dd, aa, X[4], 8);
    II(aa, bb, cc, dd, X[13], 9);
    II(dd, aa, bb, cc, X[3], 14);
    II(cc, dd, aa, bb, X[7], 5);
    II(bb, cc, dd, aa, X[15], 6);
    II(aa, bb, cc, dd, X[14], 8);
    II(dd, aa, bb, cc, X[5], 6);
    II(cc, dd, aa, bb, X[6], 5);
    II(bb, cc, dd, aa, X[2], 12);

    /* parallel round 4 */
    FFF(aaa, bbb, ccc, ddd, X[8], 15);
    FFF(ddd, aaa, bbb, ccc, X[6], 5);
    FFF(ccc, ddd, aaa, bbb, X[4], 8);
    FFF(bbb, ccc, ddd, aaa, X[1], 11);
    FFF(aaa, bbb, ccc, ddd, X[3], 14);
    FFF(ddd, aaa, bbb, ccc, X[11], 14);
    FFF(ccc, ddd, aaa, bbb, X[15], 6);
    FFF(bbb, ccc, ddd, aaa, X[0], 14);
    FFF(aaa, bbb, ccc, ddd, X[5], 6);
    FFF(ddd, aaa, bbb, ccc, X[12], 9);
    FFF(ccc, ddd, aaa, bbb, X[2], 12);
    FFF(bbb, ccc, ddd, aaa, X[13], 9);
    FFF(aaa, bbb, ccc, ddd, X[9], 12);
    FFF(ddd, aaa, bbb, ccc, X[7], 5);
    FFF(ccc, ddd, aaa, bbb, X[10], 15);
    FFF(bbb, ccc, ddd, aaa, X[14], 8);

    tmp = dd;
    dd = ddd;
    ddd = tmp;

    /* combine results */
    MDbuf[0] += aa;
    MDbuf[1] += bb;
    MDbuf[2] += cc;
    MDbuf[3] += dd;
    MDbuf[4] += aaa;
    MDbuf[5] += bbb;
    MDbuf[6] += ccc;
    MDbuf[7] += ddd;
}

void RipeMD_256::MDfinish(unsigned char *message, ulong lenth, ulong mswlen) { // 结束处理部分
    // mswlen = 0
    ulong X[16]; // message words

    memset(X, 0, 16 * sizeof(ulong));

    // 将来自message的字节放入X
    for (unsigned int i = 0; i < (lenth & 63); i++)
        X[i >> 2] ^= (ulong) *message++ << (8 * (i & 3));

    // append the bit m_n == 1
    X[(lenth >> 2) & 15] ^= (ulong) 1 << (8 * (lenth & 3) + 7);

    if ((lenth & 63) > 55) {
        // length goes to next block
        compress(X);
        memset(X, 0, 16 * sizeof(ulong));
    }

    // append length in bits
    X[14] = lenth << 3;
    X[15] = (lenth >> 29) | (mswlen << 3);
    compress(X); // 压缩函数
}

char* RipeMD_256::RMD(unsigned char *message) { // 运行函数
    unsigned char hashcode[33]; // 存储最终结果
    ulong X[16]; // 当前16字的块

    MDinit(); // 初始化
    ulong length = (ulong) strlen((char *) message); // 获取用户口令的长度

    /* process message in 16-word chunks */
    for (ulong nbytes = length; nbytes > 63; nbytes -= 64) // 尚未处理的字节数，长度模64左移处理
    {
        for (unsigned int i = 0; i < 16; i++) {
            X[i] = BytesToUlong(message); // 每次处理四个字节，存入X[i]
            message += 4; // 对指针移动
        }
        compress(X); // 压缩函数
    }

    MDfinish(message, length, 0); // 结束处理部分

    for (unsigned int i = 0; i < 32; i += 4) { // 隐式转换为字节，至少提取8个有效位
        hashcode[i] = MDbuf[i >> 2];
        hashcode[i + 1] = (MDbuf[i >> 2] >> 8);
        hashcode[i + 2] = (MDbuf[i >> 2] >> 16);
        hashcode[i + 3] = (MDbuf[i >> 2] >> 24);
    }

    char *ret = new char[256];
    for (unsigned int i = 0; i < 32; i++) {
        bitset<8> bt(hashcode[i]);
        strncpy(ret+i*8, bt.to_string().c_str(), 8);
    }

    return ret; // 返回string串
}
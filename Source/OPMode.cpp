//
// Created by 12036 on 2021/4/17.
//

#include "../Header/OPMode.h"

OPMode::OPMode(string Path, string Key, bool E_D) {
    Plaintext = "";
    res = "";
    FilaPath = Path;
    UserKey = Key;
    flag = E_D;
    InitialVector = "Be_Zero!";
}

void OPMode::ECB() {
    Key key(UserKey);
    key.MakeSubKey();
    TripleDes des;
    File_IO file_io(FilaPath);
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            res += des.Operation(key, Plaintext.substr(i, 8), 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            res += des.Operation(key, Plaintext.substr(i, 8), 0);
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

void OPMode::CBC() {
    Key key(UserKey);
    TripleDes des;
    File_IO file_io(FilaPath);
    string IV = StringToBits(InitialVector);

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(Plaintext.substr(i, 8));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(res.substr(i - 8, 8)));
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            }
            res += des.Operation(key, tmp, 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(des.Operation(key, Plaintext.substr(i, 8), 0));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(Plaintext.substr(i - 8, 8)));
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            }
            res += tmp;
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

void OPMode::CFB() {
    Key key(UserKey);
    TripleDes des;
    File_IO file_io(FilaPath);
    string IV = StringToBits(des.Operation(key, InitialVector, 1));
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(Plaintext.substr(i, 8));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(des.Operation(key, res.substr(i - 8, 8), 1)));
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            }
            res += tmp;
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(Plaintext.substr(i, 8));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(des.Operation(key, Plaintext.substr(i - 8, 8), 1)));
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            }
            res += tmp;
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

void OPMode::OFB() {
    Key key(UserKey);
    TripleDes des;
    File_IO file_io(FilaPath);
    string IV = InitialVector;
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            IV = des.Operation(key, IV, 1);
            string tmp = StringToBits(Plaintext.substr(i, 8));
            bitset<64> ep1(tmp), ep2(StringToBits(IV));
            tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            res += tmp;
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            IV = des.Operation(key, IV, 1);
            string tmp = StringToBits(Plaintext.substr(i, 8));
            bitset<64> ep1(tmp), ep2(StringToBits(IV));
            tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            res += tmp;
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

void OPMode::CTR() {
    Key key(UserKey);
    TripleDes des;
    File_IO file_io(FilaPath);
    string IV = InitialVector;
    bitset<64> add = 1;
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            bitset<64> counter(StringToBits(des.Operation(key, IV, 1)));
            string tmp = StringToBits(Plaintext.substr(i, 8));
            bitset<64> ep(tmp);
            tmp = RestorePlaintext((ep ^ counter).to_string());
            res += tmp;
            counter = OpPlus(counter, add);
            IV = RestorePlaintext(counter.to_string());
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            bitset<64> counter(StringToBits(des.Operation(key, IV, 1)));
            string tmp = StringToBits(Plaintext.substr(i, 8));
            bitset<64> ep(tmp);
            tmp = RestorePlaintext((ep ^ counter).to_string());
            res += tmp;
            counter = OpPlus(counter, add);
            IV = RestorePlaintext(counter.to_string());
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

void OPMode::PCBC() {
    Key key(UserKey);
    TripleDes des;
    File_IO file_io(FilaPath);
    string IV = StringToBits(InitialVector);

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(Plaintext.substr(i, 8));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(res.substr(i - 8, 8))), ep3(
                        StringToBits(Plaintext.substr(i - 8, 8)));
                tmp = RestorePlaintext((ep1 ^ ep2 ^ ep3).to_string());
            }
            res += des.Operation(key, tmp, 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 8) {
            string tmp = StringToBits(des.Operation(key, Plaintext.substr(i, 8), 0));
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = RestorePlaintext((ep1 ^ ep2).to_string());
            } else {
                bitset<64> ep1(tmp), ep2(StringToBits(Plaintext.substr(i - 8, 8))), ep3(
                        StringToBits(res.substr(i - 8, 8)));
                tmp = RestorePlaintext((ep1 ^ ep2 ^ ep3).to_string());
            }
            res += tmp;
        }
        file_io.Save_DE(res);
    }
    cout << "finished!" << endl;
}

string OPMode::StringToBits(string s) { // 字符串转二进制串
    string ans = "";
    for (int i = 0; i < s.size(); ++i) {
        bitset<8> tmp = s[i];
        ans += tmp.to_string();
    }
    return ans;
}

string OPMode::RestorePlaintext(string s) { // 将二进制信息转化为字节
    string res = "";

    for (int i = 0; i < s.size(); i += 8) {
        bitset<8> tmp(s.substr(i, 8));
        char ans = tmp.to_ulong();
        res += "0";
        res[res.size() - 1] = ans;
    }
    return res;
}

bitset<64> OPMode::OpPlus(bitset<64> a, bitset<64> b) {
    bitset<64> sum = a;
    bitset<64> carry = b;
    bitset<64> tmps;
    while (carry.any()) {
        tmps = sum;
        sum = tmps ^ carry; // 求非进位结果
        carry = (tmps & carry) << 1; // 求进位结果（两个相加等于最终结果）
    }
    return sum; // 进位结果等于0时，结束。
}
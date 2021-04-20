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
        for (int i = 0; i < Plaintext.size(); i += 64) {
            res += des.Operation(key, Plaintext.substr(i, 64), 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            res += des.Operation(key, Plaintext.substr(i, 64), 0);
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
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = Plaintext.substr(i, 64);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(res.substr(i - 64, 64));
                tmp = (ep1 ^ ep2).to_string();
            }
            res += des.Operation(key, tmp, 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = des.Operation(key, Plaintext.substr(i, 64), 0);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(Plaintext.substr(i - 64, 64));
                tmp = (ep1 ^ ep2).to_string();
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
    string IV = StringToBits(InitialVector);
    IV = des.Operation(key, IV, 1);

    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = Plaintext.substr(i, 64);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(des.Operation(key, res.substr(i - 64, 64), 1));
                tmp = (ep1 ^ ep2).to_string();
            }
            res += tmp;
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = Plaintext.substr(i, 64);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(des.Operation(key, Plaintext.substr(i - 64, 64), 1));
                tmp = (ep1 ^ ep2).to_string();
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
    string IV = StringToBits(InitialVector);
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            IV = des.Operation(key, IV, 1);
            string tmp = Plaintext.substr(i, 64);
            bitset<64> ep1(tmp), ep2(IV);
            tmp = (ep1 ^ ep2).to_string();
            res += tmp;
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            IV = des.Operation(key, IV, 1);
            string tmp = Plaintext.substr(i, 64);
            bitset<64> ep1(tmp), ep2(IV);
            tmp = (ep1 ^ ep2).to_string();
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
    string IV = StringToBits(InitialVector);
    bitset<64> add = 1;
    if (flag) {
        Plaintext = file_io.Load_EN();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            bitset<64> counter(des.Operation(key, IV, 1));
            string tmp = Plaintext.substr(i, 64);
            bitset<64> ep(tmp);
            tmp = (ep ^ counter).to_string();
            res += tmp;
            counter = OpPlus(counter, add);
            IV = counter.to_string();
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            bitset<64> counter(des.Operation(key, IV, 1));
            string tmp = Plaintext.substr(i, 64);
            bitset<64> ep(tmp);
            tmp = (ep ^ counter).to_string();
            res += tmp;
            counter = OpPlus(counter, add);
            IV = counter.to_string();
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
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = Plaintext.substr(i, 64);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(res.substr(i - 64, 64)), ep3(
                        Plaintext.substr(i - 64, 64));
                tmp = (ep1 ^ ep2 ^ ep3).to_string();
            }
            res += des.Operation(key, tmp, 1);
        }
        file_io.Save_EN(res);
    } else {
        Plaintext = file_io.Load_DE();
        for (int i = 0; i < Plaintext.size(); i += 64) {
            string tmp = des.Operation(key, Plaintext.substr(i, 64), 0);
            if (i == 0) {
                bitset<64> ep1(tmp), ep2(IV);
                tmp = (ep1 ^ ep2).to_string();
            } else {
                bitset<64> ep1(tmp), ep2(Plaintext.substr(i - 64, 64)), ep3(
                        res.substr(i - 64, 64));
                tmp = (ep1 ^ ep2 ^ ep3).to_string();
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
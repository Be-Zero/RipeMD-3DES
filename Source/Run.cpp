//
// Created by Bezero on 2021/4/12.
//

#include "../Header/Run.h"

int main() {
    string EnFilePath = "../test/test.png";
    string DeFilePath = "../test/test_En.png";
    string UserKey = "qth";
    OPMode ep1(EnFilePath, UserKey, 1);
    ep1.CBC();
    OPMode ep2(DeFilePath, UserKey, 0);
    ep2.CBC();
    return 0;
}
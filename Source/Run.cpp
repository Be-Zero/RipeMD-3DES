//
// Created by Bezero on 2021/4/12.
//

#include "../Header/Run.h"

int main() {
    clock_t t;
    char *EnFilePath = "../test/test.txt";
    char *DeFilePath = "../test/test_En.txt";
    char *UserKey = "qth";
    OPMode ep1(EnFilePath, UserKey, 1);
    t=clock();
    ep1.CBC();
    cout<<"en:"<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    OPMode ep2(DeFilePath, UserKey, 0);
    t=clock();
    ep2.CBC();
    cout<<"de:"<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    return 0;
}

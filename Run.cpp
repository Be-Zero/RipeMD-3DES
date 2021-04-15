//
// Created by Bezero on 2021/4/12.
//

#include "Run.h"

int main() {
    Key key("qwerasdfzxcvbnm,uiopyhkdbtsk. 84");
    File_IO file_En("../test/test.txt");
    file_En.Operation(1, key);
    File_IO file_DE("../test/test_En.txt");
    file_DE.Operation(0, key);
    return 0;
}

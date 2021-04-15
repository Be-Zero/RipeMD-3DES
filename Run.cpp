//
// Created by Bezero on 2021/4/12.
//

#include "Run.h"

int main() {
    Key key("qwerasdfzxcvbnm,uiopyhkdbtsk. 84");
    File_IO file("../test/test.txt");
    file.Operation(1, key);
    file.Operation(0, key);
    return 0;
}

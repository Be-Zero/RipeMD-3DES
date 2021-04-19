#include "../Header/system_ui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System_UI w;
    w.show();
    return a.exec();
}
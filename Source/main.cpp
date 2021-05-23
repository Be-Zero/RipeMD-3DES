#include "../Header/system_ui.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System_UI *w = new System_UI();
    w->show();
    return a.exec();
}

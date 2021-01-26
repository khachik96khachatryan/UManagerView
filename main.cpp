#include <QApplication>
#include "umanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UManager um;
    um.show();

    return a.exec();
}

#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QApplication a1(argc, argv);
    Server s("127.0.0.1", 1234);



    return a1.exec();
    return a.exec();
}

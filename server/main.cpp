#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s("127.0.0.1", 1234);
    QApplication a1(argc, argv);
    s.createForm();
    s.dbform->show();
    return a1.exec();
    return a.exec();
}

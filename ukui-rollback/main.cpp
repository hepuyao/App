#include "ukuirollback.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UKuiRollback w;
    w.show();
    return a.exec();
}

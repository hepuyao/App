#include "mainwindow.h"

#include <QApplication>
#include <KWindowEffects>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    KWindowEffects::enableBlurBehind(w.winId(),true);

    return a.exec();
}

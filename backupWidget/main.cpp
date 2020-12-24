#include "mainwindow.h"

#include <QApplication>
#include <KWindowEffects>

#include "xatom-helper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    KWindowEffects::enableBlurBehind(w.winId(),true);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);

    return a.exec();
}

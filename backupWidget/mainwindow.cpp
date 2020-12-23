#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[this]{
        animalionWidget();

        QDBusInterface iface("com.test.qt.systemdbus",
                             "/",
                             "com.test.interface",
                             QDBusConnection::systemBus());
        iface.call("modifyPropFile","rollback","f");
        iface.call("updateGrub");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[this]{
        system("reboot");
    });

    QDBusConnection::sessionBus().connect(QString(), QString("/"), "com.ukui.backup.plugins", "sendToUkuiDEApp", this, SLOT(client_get()));

    ui->pushButton_3->setVisible(false);

    timer=new QTimer;
    connect(timer,&QTimer::timeout,[this] {
        QApplication::exit();
    });
    timer->start(300000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::client_get()
{
    timer->stop();
    ui->pushButton_3->setVisible(false);
}

void MainWindow::animalionWidget()
{
    timer->stop();
    ui->pushButton_3->setVisible(true);
    ui->pushButton_3->setText(">>>>>>>>>>>>>>>>>");
}

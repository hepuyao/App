#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon::fromTheme("distributor-logo-kylin"));
    this->setWindowTitle("备份还原");
    connect(ui->pushButton,&QPushButton::clicked,[this]{
        animalionWidget();

        QDBusInterface iface("com.ukui.backup.qt.systemdbus",
                             "/",
                             "com.ukui.backup.interface",
                             QDBusConnection::systemBus());
        iface.call("modifyPropFile","rollback","fase");
        iface.call("updateGrub");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[this]{
        system("reboot");
    });

    QDBusConnection::systemBus().connect(QString(), QString("/"), "com.ukui.backup.interface", "sendToUkuiDEApp", this, SLOT(client_get()));

    ui->label_2->setVisible(false);

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
    ui->label_2->setVisible(false);
}

void MainWindow::animalionWidget()
{
    ui->label_2->setVisible(true);

    movie = new QMovie(":/loading.gif");

    QTimer *movieTimer=new QTimer;
    connect(movieTimer,&QTimer::timeout,[this] {
        movie->stop();
        ui->label_2->setVisible(false);
    });

    ui->label_2->setMovie(movie);

    movie->setScaledSize(ui->label_2->size());
    movie->start();

}

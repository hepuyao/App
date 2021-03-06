#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QMovie>


#define TRANSPARENCY_SETTINGS       "org.ukui.control-center.personalise"
#define TRANSPARENCY_KEY            "transparency"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
     *  在这里仍然设置了窗口图标和标题，但实际上已经重新绘了标题栏
     *  这里不需要设置去掉标题栏属性的原因是窗管已经处理了
     *  this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    */
    this->setWindowIcon(QIcon::fromTheme("distributor-logo-kylin"));
    this->setWindowTitle("备份还原");

    setAttribute(Qt::WA_TranslucentBackground);
    initWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    initTitleBar();
    connectButtonClicked();
    widgetPaint();


    QDBusConnection::systemBus().connect(QString(), QString("/"), "com.ukui.backup.interface", "UpdateGrubFinished", this, SLOT(client_get()));

    ui->label_2->setVisible(false);

    timer=new QTimer;
    connect(timer,&QTimer::timeout,[this] {
        QApplication::exit();
    });
    timer->start(300000);


}

void MainWindow::initTitleBar()
{
    ui->menubar->setVisible(false);
    ui->label->setText("请选择是否回滚");

    ui->pushButton->setText("确认回滚");


    ui->pushButton_3->setIcon(QIcon::fromTheme("distributor-logo-kylin"));
    ui->pushButton_3->setFixedSize(30, 30);
    ui->pushButton_3->setIconSize(QSize(24, 24));
    ui->pushButton_3->setProperty("isWindowButton", 0x1);
    ui->pushButton_3->setProperty("useIconHighlightEffect", 0x2);
    ui->pushButton_3->setFlat(true);

    ui->label_3->setText("备份还原");

    ui->pushButton_4->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    ui->pushButton_4->setFixedSize(30, 30);
    ui->pushButton_4->setIconSize(QSize(16, 16));
    ui->pushButton_4->setProperty("isWindowButton", 0x1);
    ui->pushButton_4->setProperty("useIconHighlightEffect", 0x2);
    ui->pushButton_4->setFlat(true);

    ui->pushButton_5->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButton_5->setFixedSize(30, 30);
    ui->pushButton_5->setIconSize(QSize(16, 16));
    ui->pushButton_5->setProperty("isWindowButton", 0x2);
    ui->pushButton_5->setProperty("useIconHighlightEffect", 0x8);
    ui->pushButton_5->setFlat(true);
}

void MainWindow::connectButtonClicked()
{
    connect(ui->pushButton,&QPushButton::clicked,[this]{
        animalionWidget();

        QDBusInterface iface("com.ukui.backup.qt.systemdbus",
                             "/",
                             "com.ukui.backup.interface",
                             QDBusConnection::systemBus());
        iface.call("RdmssMount");
        iface.call("RdmssSetkey","rollback","false");
        iface.call("RdmssSetkey","active_B","true");
        iface.call("RdmssSetkey","bootable_B","true");
        iface.call("RdmssUpdate");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[this]{
        system("reboot");
    });

    connect(ui->pushButton_4,&QPushButton::clicked,[this]{
        onMin(true);
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[this]{
        onClose(true);
    });

}

void MainWindow::widgetPaint()
{
    const QByteArray transparency_id(TRANSPARENCY_SETTINGS);
    if(QGSettings::isSchemaInstalled(transparency_id)){
        transparency_gsettings = new QGSettings(transparency_id);
        //setPanelBackground(true);
    }
    connect(transparency_gsettings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==TRANSPARENCY_KEY)
        {
            //setPanelBackground(true);
            this->update();
        }
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    double tran=transparency_gsettings->get(TRANSPARENCY_KEY).toDouble()*255;
    QColor color = palette().color(QPalette::Base);
    color.setAlpha(tran);
    QBrush brush =QBrush(color);
    p.setBrush(brush);

    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(opt.rect,12,12);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void MainWindow::client_get()
{
    ui->label_2->setVisible(false);
}

void MainWindow::animalionWidget()
{
    ui->label_2->setVisible(true);
    movie = new QMovie(":/load.gif");
    QTimer *movieTimer=new QTimer;
    connect(movieTimer,&QTimer::timeout,[this] {
        movie->stop();
        ui->label_2->setVisible(false);
    });
    ui->label_2->setMovie(movie);
    movie->setScaledSize(ui->label_2->size());
    movie->start();

}

//按钮的最大化，最小化，关闭选项
void MainWindow::onMin(bool)
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}

void MainWindow::onMaxOrNormal(bool)
{
    setWindowState( Qt::WindowMaximized );
}

void MainWindow::onClose(bool)
{
    close();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGSettings/QGSettings>

#include <QToolButton>
#include <QDBusInterface>
#include <QDBusReply>
#include <QTimer>

//ui
#include <QStyleOption>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief initWidget
     * 初始化widget
     */
    void initWidget();
    /**
     * @brief initTitleBar
     * 初始化标题栏
     */
    void initTitleBar();
    /**
     * @brief connectButtonClicked
     * 按钮点击
     */
    void connectButtonClicked();
    /**
     * @brief widgetPaint
     * 界面绘制
     */
    void widgetPaint();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMovie *movie;

    QGSettings *transparency_gsettings;

private Q_SLOTS:
    /**
     * @brief client_get
     * 监听更新grub更新完成的信号，loading界面消失
     */
    void client_get();
    /**
     * @brief animalionWidget
     * 更新过程中的动画效果
     */
    void animalionWidget();

    //按钮的最大化，最小化，关闭选项
    void onMin( bool );
    void onMaxOrNormal( bool );
    void onClose( bool );

};
#endif // MAINWINDOW_H

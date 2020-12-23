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

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMovie *movie;

    QGSettings *transparency_gsettings;

private Q_SLOTS:
    void client_get();
    void animalionWidget();

    //button
    void onMin( bool );
    void onMaxOrNormal( bool );
    void onClose( bool );

};
#endif // MAINWINDOW_H

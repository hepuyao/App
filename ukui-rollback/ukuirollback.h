#ifndef UKUIROLLBACK_H
#define UKUIROLLBACK_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class UKuiRollback; }
QT_END_NAMESPACE

class UKuiToolButton;
class UKuiRollback : public QMainWindow
{
    Q_OBJECT

public:
    UKuiRollback(QWidget *parent = nullptr);
    ~UKuiRollback();

private:
//    QHash<QString,QString,int> findRollBackItem();
    /**
     * @brief addLabel
     */
    void addLabel();

    Ui::UKuiRollback *ui;
    int size;
//    QHash<QString, QString,int> m_fallBackHash;
//    struct RoolBack
//    {
//        int empNumber;
//        string name;
//        double hours,payRate,grossPay;
//    };
};

class UKuiToolButton : public QToolButton
{
    Q_OBJECT

public:
    UKuiToolButton();
    ~UKuiToolButton();

    void initUKuiToolButton(QString name, QString iconname,int id);

private:

    int rollbackId;
};
#endif // UKUIROLLBACK_H

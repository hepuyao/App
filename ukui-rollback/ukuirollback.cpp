#include "ukuirollback.h"
#include "ui_ukuirollback.h"

UKuiRollback::UKuiRollback(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UKuiRollback)
{
    size=5;
    ui->setupUi(this);
    //find rollback item

    //add rollback system
    addLabel();

}

UKuiRollback::~UKuiRollback()
{
    delete ui;
}

//QHash<QString,QString,int> UKuiRollback::findRollBackItem()
//{
////    m_fallBackHash.insert();
//}
/**
 * @brief UKuiRollback::addLabel
 */
void UKuiRollback::addLabel()
{
    for(int i=0;i< size;i++)
    {
        UKuiToolButton *btn;
        btn=new UKuiToolButton;
        btn->initUKuiToolButton("name","firefox",3);
        ui->verticalLayout->addWidget(btn);
    }
}


UKuiToolButton::UKuiToolButton()
{
}

UKuiToolButton::~UKuiToolButton()
{

}

void UKuiToolButton::initUKuiToolButton(QString name, QString iconname,int id)
{
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->setIcon(QIcon::fromTheme(iconname));
    this->setText(name);
    rollbackId=id;
}

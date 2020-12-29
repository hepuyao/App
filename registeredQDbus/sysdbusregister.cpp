/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#include "sysdbusregister.h"

#include <QDebug>
#include <QSharedPointer>
#include <QRegExp>
#include <stdlib.h>
#include <QProcess>

SysdbusRegister::SysdbusRegister()
{
    mHibernateFile = "/etc/systemd/sleep.conf";
    mHibernateSet = new QSettings(mHibernateFile, QSettings::IniFormat, this);
    mHibernateSet->setIniCodec("UTF-8");

//    QDBusConnection::sessionBus().unregisterService("com.ukui.backup.plugins");
//    QDBusConnection::sessionBus().registerService("com.ukui.backup.plugins");
//    QDBusConnection::sessionBus().registerObject("/", this,QDBusConnection :: ExportAllSlots | QDBusConnection :: ExportAllSignals);
}

SysdbusRegister::~SysdbusRegister()
{
}

void SysdbusRegister::exitService() {
    qApp->exit(0);
}

QString SysdbusRegister::GetComputerInfo() {
    QByteArray ba;
    FILE * fp = NULL;
    char cmd[128];
    char buf[1024];
    sprintf(cmd, "dmidecode -t system");

    if ((fp = popen(cmd, "r")) != NULL){
        rewind(fp);
        while (!feof(fp)) {
            fgets(buf, sizeof (buf), fp);
            ba.append(buf);
        }
        pclose(fp);
        fp = NULL;
    }
    return QString(ba);
}

void SysdbusRegister::modifyPropFile(QString key,QString value) {
    QString modifyPropFileCmd="modifyPropFile %1 %2";
    modifyPropFileCmd=modifyPropFileCmd.arg(key).arg(value);
    char*  ch;
    QByteArray ba = modifyPropFileCmd.toLatin1();
    ch=ba.data();

    system(ch);
}

void SysdbusRegister::updateGrub() {
    QProcess *process = new QProcess();
    process->start(QString("updateRollback"));
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(finished(int,QProcess::ExitStatus)));
}

void SysdbusRegister::finished(int exitCode,QProcess::ExitStatus exitStatus)
{
    /*创建QT的DBus信号*/
    QDBusMessage message =QDBusMessage::createSignal("/", "com.ukui.backup.interface", "UpdateGrubFinished");
    QDBusConnection::systemBus().send(message);
}

bool SysdbusRegister::RdmssMount()
{
//    system("kylin-rdmss-tools mount");
    FILE *fp=popen("kylin-rdmss-tools mount","r");
    char *cur_system_uuid;
    if (fp) {
        fgets(cur_system_uuid, 1024, fp);
    }
    if(strcmp(cur_system_uuid,"\n")==0) return true;
    else return false;

}

void SysdbusRegister::RdmssUmount()
{
    system("kylin-rdmss-tools umount");
}
void SysdbusRegister::RdmssMerge(QString str1,QString str2)
{
    QString mergeCmd="kylin-rdmss-tools merge %1 %2";
    system(mergeCmd.arg(str1).arg(str2).toLatin1().data());
}
void SysdbusRegister::RdmssCreate()
{
    system("kylin-rdmss-tools create");
}
void SysdbusRegister::RdmssRestore(QString str1,QString str2)
{
    QString restoreCmd="kylin-rdmss-tools restore %1 %2";
    system(restoreCmd.arg(str1).arg(str2).toLatin1().data());
}
void SysdbusRegister::RdmssChain()
{
    system("kylin-rdmss-tools chain");
}

void SysdbusRegister::RdmssDetails()
{
    system("kylin-rdmss-tools details");
}
QString SysdbusRegister::RdmssGetKey(QString str)
{
    char cmd[1024]={0};
    char line[1024]={0};

    char*  ch;
    ch=str.toLatin1().data();
    snprintf(cmd,1024,"kylin-rdmss-tools getkey -k %s",ch);
    FILE *fp=popen(cmd,"r");
    if (fp) {
        fgets(line, 1024, fp);
        line[strlen(line)-1]='\0';
    }
    pclose(fp);
    QByteArray ba;
    ba.append(line);
    return QString(ba);
}

void SysdbusRegister::RdmssSetkey(QString str1,QString str2)
{
    QString setKeyCmd="kylin-rdmss-tools setkey -k %1  -v %2";
    system(setKeyCmd.arg(str1).arg(str2).toLatin1().data());
}

void SysdbusRegister::RdmssUpdate()
{
//    system("kylin-rdmss-tools update");
    QProcess *process = new QProcess();
    process->start(QString("kylin-rdmss-tools update"));
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(finished(int,QProcess::ExitStatus)));
}

void SysdbusRegister::RdmssInit()
{
    system("kylin-rdmss-tools init");
}

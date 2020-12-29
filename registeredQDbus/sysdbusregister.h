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
#ifndef SYSDBUSREGISTER_H
#define SYSDBUSREGISTER_H

#include <QObject>
#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QSettings>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QMessageBox>

#include <stdio.h>
class SysdbusRegister : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "com.ukui.backup.interface")

public:
    explicit SysdbusRegister();
    ~SysdbusRegister();

private:
    QString mHibernateFile;

    QSettings *mHibernateSet;

signals:
    Q_SCRIPTABLE void nameChanged(QString);
    Q_SCRIPTABLE void computerinfo(QString);

public slots:

    Q_SCRIPTABLE void exitService();
    Q_SCRIPTABLE QString GetComputerInfo();

    // 修改日志文件
    Q_SCRIPTABLE void modifyPropFile(QString,QString);
    // 删除grub
    Q_SCRIPTABLE void updateGrub();
	//挂载
    Q_SCRIPTABLE bool RdmssMount();
    //卸载
    Q_SCRIPTABLE void RdmssUmount();
    //合并
    Q_SCRIPTABLE void RdmssMerge(QString , QString );
    //创建
    Q_SCRIPTABLE void RdmssCreate();
    //恢复
    Q_SCRIPTABLE void RdmssRestore(QString , QString );
    //
    Q_SCRIPTABLE void RdmssChain();
    //
    Q_SCRIPTABLE void RdmssDetails();
    //
    Q_SCRIPTABLE QString RdmssGetKey(QString);
    //
    Q_SCRIPTABLE void RdmssSetkey(QString , QString);
    //更新
    Q_SCRIPTABLE void RdmssUpdate();
    //初始化
    Q_SCRIPTABLE void RdmssInit();


private slots:
    void finished(int exitCode,QProcess::ExitStatus exitStatus);
};

#endif // SYSDBUSREGISTER_H

QT       += core gui dbus KWindowSystem x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    xatom-helper.cpp

HEADERS += \
    mainwindow.h \
    xatom-helper.h

FORMS += \
    mainwindow.ui

# 适配窗口管理器圆角阴影
LIBS +=-lpthread
LIBS +=-lX11

PKGCONFIG+=glib-2.0 gio-unix-2.0 gsettings-qt
CONFIG += no_keywords link_pkgconfig

# Default rules for deployment.
qnx: target.path = /usr/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

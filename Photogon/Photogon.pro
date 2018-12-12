#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T20:12:39
#
#-------------------------------------------------

QT       += core gui
QT += network
QT_CONFIG -= no-pkg-config

CONFIG += link_pkgconfig

CONFIG += app_bundle

PKGCONFIG += opencv

LIBS += -L/usr/local/Cellar/opencv/3.4.3/lib/

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Photogon
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z

3QMAKE_CXXFLAGS += -std=c++17

CONFIG+=sdk_no_version_check

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    computervision.cpp \
    worker.cpp \
    windowstartup.cpp \
    newproject.cpp \
    themainwindow.cpp \
    camera.cpp \
    calibrationmask.cpp \
    cameradiscovery.cpp \
    myudp.cpp \
    inputdialog.cpp \
    showmask.cpp \
    showhistogram.cpp \
    showshape.cpp

HEADERS += \
        mainwindow.h \
    computervision.h \
    worker.h \
    windowstartup.h \
    newproject.h \
    themainwindow.h \
    camera.h \
    calibrationmask.h \
    cameradiscovery.h \
    myudp.h \
    inputdialog.h \
    showmask.h \
    showhistogram.h \
    showshape.h

FORMS += \
        mainwindow.ui \
    testwindow.ui \
    windowstartup.ui \
    newproject.ui \
    themainwindow.ui \
    camera.ui \
    calibrationmask.ui \
    cameradiscovery.ui \
    showmask.ui \
    showhistogram.ui \
    showshape.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

mac {
    CONFIG += x86
    plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
    plist.files = Info.plist
    INSTALLS += plist

}

RESOURCES += \
    icons.qrc

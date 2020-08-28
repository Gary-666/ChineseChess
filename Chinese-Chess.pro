#-------------------------------------------------
#
# Project created by QtCreator 2020-05-31
#
#
#关于作者:
#华南理工大学 2019级软件工程(3)班 马嘉锐
#作品完成时间:2020-06-28
#作品用途: C++大作业
#其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏。
#
#联系作者:
#GitHub:        https://github.com/Gary-666
#-------------------------------------------------

QT       += core gui multimedia

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
    Board.cpp \
    GameScene.cpp \
    MachineGame.cpp \
    MachineGameSelect.cpp \
    NetGame.cpp \
    OpenGame.cpp \
    Step.cpp \
    Stone.cpp \
    WinGame.cpp \
    main.cpp
QT+=widgets gui network

HEADERS += \
    Board.h \
    GameScene.h \
    MachineGame.h \
    MachineGameSelect.h \
    NetGame.h \
    OpenGame.h \
    Step.h \
    Stone.h \
    WinGame.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    GameScene.ui \
    OpenGame.ui \
    machinegameselect.ui

RESOURCES += \
    RES.qrc

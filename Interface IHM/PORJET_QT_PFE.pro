QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    module.cpp

HEADERS += \
    mainpage.h \
    mainwindow.h \
    module.h

FORMS += \
    mainpage.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    actionneur.qrc \
    automa.qrc \
    buz.qrc \
    capteur.qrc \
    car.qrc \
    centl.qrc \
    cloud.qrc \
    date.qrc \
    distance.qrc \
    essuiact.qrc \
    fancmd.qrc \
    ima.qrc \
    image2.qrc \
    imgg.qrc \
    password.qrc \
    rpm.qrc \
    temp.qrc \
    time.qrc \
    time2.qrc \
    user.qrc \
    wipe.qrc

DISTFILES +=

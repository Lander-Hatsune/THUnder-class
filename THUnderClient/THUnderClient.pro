QT       += core gui
QT += multimedia widgets

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
    view/ansprobdialog.cpp \
    controller/stuop.cpp \
    main.cpp \
    model/Socket.cpp \
    model/adminclient.cpp \
    model/client.cpp \
    model/stuclient.cpp \
    model/teacherclient.cpp \
    controller/adminop.cpp \
    controller/loginop.cpp \
    controller/teacherop.cpp \
    view/pushprobdialog.cpp \
    view/stumainpage.cpp \
    view/teachermainpage.cpp \
    view/adminmainpage.cpp \
    view/loginpage.cpp

HEADERS += \
    view/ansprobdialog.h \
    definitions.h \
    model/Socket.h \
    model/adminclient.h \
    model/client.h \
    controller/adminop.h \
    controller/loginop.h \
    controller/stuop.h \
    controller/teacherop.h \
    model/stuclient.h \
    model/teacherclient.h \
    view/pushprobdialog.h \
    view/stumainpage.h \
    view/teachermainpage.h \
    view/adminmainpage.h \
    view/loginpage.h

FORMS += \
    view/ansprobdialog.ui \
    view/pushprobdialog.ui \
    view/stumainpage.ui \
    view/teachermainpage.ui \
    view/adminmainpage.ui \
    view/loginpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lws2_32
CONFIG += console thread

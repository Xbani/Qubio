QT       += core gui

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
    objects/blocks/qusolidblock.cpp \
    objects/blocks/quspawnblock.cpp \
    objects/entities/qucharacter.cpp \
    objects/entities/quplayablecharacter.cpp \
    objects/entities/quunplayablecharacter.cpp \
    objects/quentity.cpp \
    objects/qublock.cpp \
    objects/quobject.cpp \
    objects/ui/buttons/qubuttonclose.cpp \
    objects/ui/buttons/qubuttongohost.cpp \
    objects/ui/buttons/qubuttongojoin.cpp \
    objects/ui/buttons/qubuttonhost.cpp \
    objects/ui/buttons/qubuttonjoin.cpp \
    objects/ui/buttons/qubuttonsolo.cpp \
    objects/ui/buttons/qubuttontitle.cpp \
    objects/ui/qubutton.cpp \
    objects/ui/buttons/qubuttonmulti.cpp \
    objects/ui/qutextbox.cpp \
    qugameengine.cpp \
    rooms/ui/quuihost.cpp \
    rooms/quui.cpp \
    rooms/ui/quuimainmenu.cpp \
    rooms/ui/quuimultiplayer.cpp

HEADERS += \
    mainwindow.h \
    objects/blocks/qusolidblock.h \
    objects/blocks/quspawnblock.h \
    objects/entities/qucharacter.h \
    objects/entities/quplayablecharacter.h \
    objects/entities/quunplayablecharacter.h \
    objects/quentity.h \
    objects/qublock.h \
    objects/quobject.h \
    objects/ui/buttons/qubuttonclose.h \
    objects/ui/buttons/qubuttongohost.h \
    objects/ui/buttons/qubuttongojoin.h \
    objects/ui/buttons/qubuttonhost.h \
    objects/ui/buttons/qubuttonjoin.h \
    objects/ui/buttons/qubuttonsolo.h \
    objects/ui/buttons/qubuttontitle.h \
    objects/ui/qubutton.h \
    objects/ui/buttons/qubuttonmulti.h \
    objects/ui/qutextbox.h \
    qugameengine.h \
    rooms/ui/quuihost.h \
    rooms/quui.h \
    rooms/ui/quuimainmenu.h \
    rooms/ui/quuimultiplayer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

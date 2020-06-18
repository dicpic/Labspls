include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../source/repos/yes/IKeypad.h \
        ../../source/repos/yes/ILatch.h \
        ../../source/repos/yes/lockcontroller.h \
        tst_testdivisionbyzero.h

SOURCES += \
        ../../source/repos/yes/lockcontroller.cpp \
        main.cpp
INCLUDEPATH += "C:\Users\User\source\repos\yes"

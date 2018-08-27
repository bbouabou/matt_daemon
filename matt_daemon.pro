TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Tintin_reporter.cpp \
    CDaemon.cpp

HEADERS += \
    Tintin_reporter.h \
    CDaemon.h \
    matt_daemon.h

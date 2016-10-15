TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Data.cpp \
    Operation.cpp \
    Bierwirth.cpp

HEADERS += \
    Data.h \
    Operation.h \
    Bierwirth.h

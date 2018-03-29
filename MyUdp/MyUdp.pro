TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lWs2_32
#-lWs2_32 link WS2_32.lib
SOURCES += main.cpp \
    udp.c

HEADERS += \
    udp.h

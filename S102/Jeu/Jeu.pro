TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        autre.cpp \
    ennemie.cpp \
        main.cpp \
        player.cpp \
        vecteur.cpp \

include(MinGL2_IUT_AIX-master/mingl.pri)

HEADERS += \
    autre.h \
    ennemie.h \
    player.h \
    vecteur.h \

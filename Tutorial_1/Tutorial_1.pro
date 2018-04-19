TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/bullet
LIBS += -lBulletCollision
LIBS += -lBulletDynamics
LIBS += -lLinearMath

LIBS += -lSDL
LIBS += -lGL
LIBS += -lGLU

SOURCES += \
    camera.cpp \
    opengl.cpp \
    vector3d.cpp

HEADERS += \
    camera.h \
    vector3d.h

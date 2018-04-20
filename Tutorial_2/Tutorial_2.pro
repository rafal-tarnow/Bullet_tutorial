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
    vector3d.cpp \
    main.cpp \
    physics_engine.cpp

HEADERS += \
    camera.h \
    vector3d.h \
    physics_engine.hpp

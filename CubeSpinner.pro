QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++11

SOURCES += \
        main.cpp \
        cubeview.cpp

HEADERS += \
        cubeview.h

RESOURCES += shaders.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

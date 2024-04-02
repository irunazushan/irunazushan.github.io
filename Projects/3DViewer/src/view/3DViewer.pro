QT       += core gui opengl openglwidgets widgets

include(qgifimage/gifimage/qtgifimage.pri)

CONFIG += c++17

SOURCES += \
    ../model/s21_affine_transformation.c \
    ../model/s21_parser.c \
    customopenglwidget.cc \
    main.cc \
    mainwindow.cc

HEADERS += \
    ../model/s21_affine_transformation.h \
    ../model/s21_parser.h \
    customopenglwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/../model/

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

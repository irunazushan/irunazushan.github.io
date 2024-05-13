QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/calculator_controller.cc \
    ../controller/credit_controller.cc \
    ../controller/deposit_controller.cc \
    ../model/calculator_model.cc \
    ../model/credit_model.cc \
    ../model/deposit_model.cc \
    calculator_view.cc \
    credit_view.cc \
    deposit_view.cc \
    main.cc \
    qcustomplot.cc

HEADERS += \
    ../controller/calculator_controller.h \
    ../controller/credit_controller.h \
    ../controller/deposit_controller.h \
    ../model/calculator_model.h \
    ../model/credit_model.h \
    ../model/deposit_model.h \
    calculator_view.h \
    credit_view.h \
    deposit_view.h \
    qcustomplot.h


FORMS += \
    calculator_view.ui \
    credit_view.ui \
    deposit_view.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recourse/img.qrc

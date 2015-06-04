#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T13:44:12
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrayTracer
TEMPLATE = app


SOURCES += main.cpp \
    softWarePainter.cpp \
    Tcolor.cpp \
    Tray.cpp \
    Tsphere.cpp \
    TbaseGeometry.cpp \
    TintersectionResult.cpp \
    Tcamera.cpp \
    Tscene.cpp \
    TrayTracer.cpp \
    Tplane.cpp \
    TdirectionalLight.cpp \
    TbaseLight.cpp \
    Ttexture2D.cpp \
    TblinnPhongMaterial.cpp \
    Tmaterial.cpp \
    TglassyMaterial.cpp

HEADERS  += \
    softWarePainter.h \
    Tcolor.h \
    Tray.h \
    Tsphere.h \
    TbaseGeometry.h \
    TintersectionResult.h \
    Tcamera.h \
    Tscene.h \
    TrayTracer.h \
    Tplane.h \
    TdirectionalLight.h \
    TbaseLight.h \
    Ttexture2D.h \
    TblinnPhongMaterial.h \
    Tmaterial.h \
    TglassyMaterial.h

FORMS    +=
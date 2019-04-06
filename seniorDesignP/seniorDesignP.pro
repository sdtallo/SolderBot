TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    gcode_decoder.c \
    location_list.c \
    reference_loc.c \
    arrayConst.c

HEADERS += \
    location_list.h \
    reference_loc.h \
    arrayConst.h \
    gcode_decoder.h

DISTFILES +=

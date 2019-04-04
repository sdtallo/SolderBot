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
    gcode_decoder.h \
    location_list.h \
    reference_loc.h \
    arrayConst.h

DISTFILES +=

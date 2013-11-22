#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T11:17:48
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = fcitx-qimpanel-configtool

LIBS += -lfcitx-qt -lfcitx-config -lfcitx-utils

SOURCES += main.cpp \
    mainwindow.cpp \
    main_model.cpp \
    skin/skinbase.cpp \
    skin/skinfcitx.cpp \
    candidate_word.cpp \
    editingskindialog.cpp \
    passwarddialog.cpp


HEADERS += mainwindow.h \
    main_model.h \
    skin/skinbase.h \
    kimpanelagenttype.h \
    candidate_word.h \
    editingskindialog.h \
    skin/skinfcitx.h \
    passwarddialog.h



FORMS += mainwindow.ui \
    editingskindialog.ui \
    passwarddialog.ui

RESOURCES += \
    main.qrc

OTHER_FILES +=

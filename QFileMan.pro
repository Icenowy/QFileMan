#-------------------------------------------------
#
# Project created by QtCreator 2013-03-31T16:46:34
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = QFileMan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    preview.cpp \
    search.cpp \
    searcherthread.cpp

HEADERS  += mainwindow.h \
    strlist.h \
    preview.h \
    searcherthread.h \
    searchwin.h

FORMS    += \
    mainwindow.ui \
    preview.ui \
    search.ui

OTHER_FILES += \
    go-up.png \
    search.png

RESOURCES += \
    main.qrc

unix|win32: LIBS += -lwv -lglib-2.0

# -------------------------------------------------
# Project created by QtCreator 2011-06-01T14:45:26
# -------------------------------------------------
TARGET = objdesktop
TEMPLATE = app
SOURCES += main.cpp \
    widget.cpp \
    snowwid.cpp \
    rain.cpp \
    autumn.cpp \
    object.cpp \
    etoile.cpp \
    fanous.cpp \
    butterfly.cpp \
    objectdesktop.cpp \
    penguin.cpp
HEADERS += widget.h \
    snowwid.h \
    rain.h \
    autumn.h \
    object.h \
    etoile.h \
    fanous.h \
    butterfly.h \
    objectdesktop.h \
    penguin.h
FORMS += widget.ui
RESOURCES += img.qrc
TRANSLATIONS =  objdesktop_ar.ts
   
CODECFORTR = UTF-8
win32:RC_FILE = myapp.rc


#install



target.path = /usr/bin/
 desktop.path = /usr/share/applications
    desktop.files =objdesktop.desktop
icon24.path = /usr/share/icons/hicolor/24x24/apps
    icon24.files =icons/hicolor/24x24/apps/objdesktop.png
icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon48.files =icons/hicolor/48x48/apps/objdesktop.png
icon128.path = /usr/share/icons/hicolor/128x128/apps
    icon128.files =icons/hicolor/128x128/apps/objdesktop.png
 icon32.path = /usr/share/icons/hicolor/32x32/apps
    icon32.files =icons/hicolor/32x32/apps/objdesktop.png
 icon64.path = /usr/share/icons/hicolor/64x64/apps
    icon64.files =icons/hicolor/64x64/apps/objdesktop.png   
    INSTALLS += target\
                desktop\
                icon24\
                icon32\
                icon64\
                icon48\
                icon128

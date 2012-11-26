TEMPLATE    = lib
TARGET      = core
DEFINES     += CORE_LIBRARY  # See Qt Ref doc, "Creating Shared Libraries"

CONFIG      += debug_and_release plugin
CONFIG      += build_all
QT          += opengl

INCLUDEPATH += include

DESTDIR     = $$(PWD)/../bin

CONFIG(debug, debug|release) {
    TARGET  = $$join(TARGET,,,d)
    MOC_DIR = build/debug
    OBJECTS_DIR = build/debug
    RCC_DIR = build/debug
} else {
    TARGET = $$join(TARGET,,,)
    MOC_DIR = build/release
    OBJECTS_DIR = build/release
    RCC_DIR = build/release
}

# GLEW
unix:INCLUDEPATH += /assig/grau-g/glew/include
win32:INCLUDEPATH += C:/lib/glew-1.5.8/include/
win32:LIBS += -LC:/lib/glew-1.5.8/lib
win32:LIBS += -lglew32
macx:LIBS += -lGLEW -install_name $$DESTDIR/libcore.dylib

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lglut
LIBS += -L/usr/lib/x86_64-linux-gnu/ -lGLU
LIBS += -L/usr/lib/fglrx/ -lGL

HEADERS	+= include/*.h
SOURCES	+= src/*.cpp

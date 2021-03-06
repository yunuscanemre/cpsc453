# type of build. this program is an application.
TEMPLATE = app

# executable to generate
TARGET = a2

# specifies special configurations that will make qmake add additional stuff to makefile,
# such as making sure uic is ran on *.ui files. See docs for details.
CONFIG += qt debug

#  qt libraries to use
QT = core gui opengl

# libraries to link against
#LIBS +=

###################################################### Related to files

INCLUDEPATH += src
HEADERS += src/*.h
SOURCES += src/*.cpp
FORMS += ui/MainWindow.ui

# Flags to pass to g++ compiler
QMAKE_CXXFLAGS += -std=c++0x -Wall

# where executable will be placed
DESTDIR = bin/ 

# where moc_* files generated by qt will go 
MOC_DIR = .build/

# where intermediate objects generated by compiler, such as *.o files, will go
OBJECTS_DIR = .build/ 

# where ui_*.h files genereated by uic will go
UI_DIR = .build/

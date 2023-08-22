QT       += core widgets
TARGET = QTProject
TEMPLATE = app 
SOURCES += main.cpp mainwindow.cpp command.cpp
HEADERS += mainwindow.h command.h
LIBS += -lboost_thread -lpthread -L/usr/lib/ -lboost_system -lboost_thread -lpthread

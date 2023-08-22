/**
 * the main class is where we defined the ManinWindow object and the application is being executed
 */
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 MainWindow window;
 window.show();

 return app.exec();
}
#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    // Creates an instance of QApplication
    QApplication a(argc, argv);

    // This is our MainWidget class containing our GUI and functionality
    MainWindow w;
    w.show(); // Show main window

    // run the application and return execs() return value/code
    return a.exec();
}
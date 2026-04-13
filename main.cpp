#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("CSCE 1101 Battle Arena");
    app.setApplicationVersion("0.1");

    MainWindow window;
    window.setWindowTitle("CSCE 1101 Battle Arena");
    window.resize(800, 600);
    window.show();

    return app.exec();
}

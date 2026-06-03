#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    // Load DAA Project Styles
    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
    }

    MainWindow w;
    w.show();
    return a.exec();
}
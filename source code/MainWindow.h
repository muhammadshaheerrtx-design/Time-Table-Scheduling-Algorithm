#include "MainWindow.h"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setStyleSheet("QMainWindow { background-color: #121212; } "
                        "QTableWidget { background-color: #1E1E1E; color: #00BCD4; gridline-color: #333; }"
                        "QPushButton { background-color: #00BCD4; color: black; border-radius: 5px; padding: 10px; }");

    auto *layout = new QHBoxLayout();
    table = new QTableWidget(8, 5);
    table->setHorizontalHeaderLabels({"Mon", "Tue", "Wed", "Thu", "Fri"});
    
    auto *btnGen = new QPushButton("Generate Timetable");
    connect(btnGen, &QPushButton::clicked, this, &MainWindow::onGenerate);

    layout->addWidget(btnGen);
    layout->addWidget(table);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);
}

void MainWindow::onGenerate() {
    // Logic to call Scheduler and populate Table
    // table->setItem(s, d, new QTableWidgetItem(courseInfo));
}
#include "editor.h"
#include "mainwindow.h"

#include <QApplication>
#include <QFont>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create Qt objects
    MainWindow w;
    Editor* editor = new Editor(&w);

    w.setCentralWidget(editor);


    // Display window
    w.showMaximized();
    return a.exec();
}

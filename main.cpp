#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w;
    if(argc == 1)
    {
        w = new MainWindow("C:");
    }
    else
    {
        w = new MainWindow(argv[1]);
    }
    w->show();
    
    return a.exec();
}

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w;
    if(argc == 1)
    {
#if defined Q_OS_WIN32
        w = new MainWindow("C:");
#elif defined Q_OS_LINUX
        w = new MainWindow("/");
#endif
    }
    else
    {
        w = new MainWindow(argv[1]);
    }
    w->show();
    
    return a.exec();
}

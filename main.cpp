#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QFileInfo>

#if defined Q_OS_LINUX
#include <stdlib.h> //for getenv()
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w;
    if(argc == 1)
    {
#if defined Q_OS_WIN32
        w = new MainWindow("C:");
#elif defined Q_OS_LINUX
        {
            QString root = QString((getenv("HOME") == NULL) ? "" : getenv("HOME"));
//            if(root[root.length()-1] != '/') root += "/";
            w = new MainWindow(root);
        }
#endif
    }
    else
    {
        w = new MainWindow(argv[1]);
    }
    w->show();
    
    return a.exec();
}

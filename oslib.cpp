#include <oslib.h>
#if defined(Q_OS_WIN32)
#include <windows.h>
#include <tchar.h>
#include <wchar.h>>
#elif defined(Q_OS_LINUX)
#include <stdlib.h>
#include <unistd.h>
#endif
void osExecute(QString path)
{
#if defined(Q_OS_WIN32)
    {
    QString str = fi.canonicalFilePath();
    wchar_t *wc = new wchar_t[str.length()+1];
    str.toWCharArray(wc);
    for(int i = 0;i<str.length()+1;i++)
    {
        wc[i] = ((wc[i] != '/') ? wc[i] : '\\');
    }
    ShellExecute(NULL,L"open",wc,NULL,NULL,SW_SHOWNORMAL);
    }
#elif defined(Q_OS_LINUX)
    system((QString("xdg-open \"") + path + QString("\"")).toStdString().c_str());
#endif
}
QString pathConv_o2a(QString rootdir,QString str)
{
    return ("/" + str.remove(0,rootdir.length()));
}

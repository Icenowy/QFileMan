#include "searcherthread.h"
#include <QMessageBox>

#ifdef WIN32
#include <windows.h>
#endif

SearcherThread::SearcherThread(Search *s)
{
    search = s;
    loc = "/";
    connect(this,SIGNAL(AddFileItem(QFileInfo)),search,SLOT(AddFileItem(QFileInfo)));
    connect(this,SIGNAL(AddStringItem(QString)),search,SLOT(AddStringItem(QString)));
}

void SearcherThread::run()
{
    QFileInfo root = QFileInfo(search->getRootdir() + loc);
    //search->AddFileItem(root);
    if(!root.isDir())
    {
        QMessageBox *mb = new QMessageBox(QMessageBox::Critical,"严重错误","选择的位置不是一个目录");
        mb->show();
        exit();
    }
    QDir *dir = new QDir(root.canonicalFilePath());
    this->RescFind(dir);
    search->Done();
}

QString SearcherThread::location()
{
    return loc;
}

void SearcherThread::setLocation(QString l)
{
    if(!this->isRunning())
        loc = l;
}

QString SearcherThread::content()
{
    return cont;
}

void SearcherThread::setContent(QString c)
{
    if(!this->isRunning())
        cont = c;
}

void SearcherThread::RescFind(QDir *dir)
{
    QRegExp *reg = new QRegExp(cont);
    QFileInfoList fis = dir->entryInfoList(QDir::NoDotAndDotDot);
    QFileInfo fi;
    foreach(fi,fis)
    {
#ifndef NDEBUG
        {
            QString debuginfo = (QString() + "Debug: Finding " + fi.canonicalFilePath());
            AddStringItem(debuginfo);
#ifdef WIN32
            {
                wchar_t *wc;
                wc = new wchar_t[debuginfo.length()+1];
                debuginfo.toWCharArray(wc);
                OutputDebugStringW(wc);
            }
#endif
        }
#else
        AddStringItem("");
#endif
        if(reg->exactMatch(fi.completeBaseName()+ "." + fi.completeSuffix()))
        {
            AddFileItem(fi);
        }
        if(fi.isDir())
        {
            RescFind(new QDir(fi.canonicalFilePath()));
        }
    }
}

void SearcherThread::AddStringItem(QString str)
{

}

void SearcherThread::AddFileItem(QFileInfo file)
{

}

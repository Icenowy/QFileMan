#ifndef SEARCHERTHREAD_H
#define SEARCHERTHREAD_H

#include <QThread>
#include <QDir>
#include "searchwin.h"

class Search;

class SearcherThread : public QThread
{
    Q_OBJECT
    //Q_THREAD

private:
    Search *search;
public:
    SearcherThread(Search *s);
    virtual ~SearcherThread();
    void run();
private:
    QString loc;
    QString cont;
public:
    QString location();
    void setLocation(QString l);
    QString content();
    void setContent(QString c);

private:
    void RescFind(QDir *dir);

public:
signals:
    void AddFileItem(QFileInfo file);
    void AddStringItem(QString str);
};

#endif // SEARCHERTHREAD_H

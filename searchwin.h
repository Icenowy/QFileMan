#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QFileInfo>
#include "searcherthread.h"

namespace Ui {
class Search;
}

class SearcherThread;

class Search : public QDialog
{
    Q_OBJECT
    
public:
    explicit Search(QString rootdir, QString path, QString str, QWidget *parent = 0);
    ~Search();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_released();

private:
    Ui::Search *ui;
private:
    QString rootdir;
private:
    SearcherThread *thread;

public slots:
    void AddFileItem(QFileInfo file);
    void AddStringItem(QString str);
    void Done();

public:
    QString getRootdir();
};

#endif // SEARCH_H

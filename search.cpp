#include "searchwin.h"
#include "ui_search.h"
#include <QMessageBox>

Search::Search(QString rootdir, QString path, QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    this->rootdir = rootdir;
    ui->lineEdit->setText(str);
    ui->lineEdit_2->setText(path);
    thread = new SearcherThread(this);
    ui->dial->setVisible(false);
}

Search::~Search()
{
    delete ui;
}

void Search::on_pushButton_clicked()
{

}

void Search::on_pushButton_released()
{
    thread->setLocation(ui->lineEdit_2->text());
    if(thread->isRunning())
    {
        thread->exit();
    }
    thread->start();
    ui->pushButton->setVisible(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->dial->setValue(0);
    ui->dial->setVisible(true);
}

void Search::AddFileItem(QFileInfo file)
{
    ui->listWidget->addItem(file.canonicalFilePath());
}

#ifndef NDEBUG
void Search::AddStringItem(QString str)
{
    ui->listWidget->addItem(str);
    ui->dial->setValue((ui->dial->value() + 1 ) % 10);
}
#else
void Search::AddStringItem(QString str)
{
    ui->dial->setValue((ui->dial->value() + 1 ) % 10);
}
#endif

QString Search::getRootdir()
{
    return this->rootdir;
}

void Search::Done()
{
    ui->dial->setVisible(false);
}

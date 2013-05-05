#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iterator>
#include "strlist.h"
#include <QMessageBox>
#include "searchwin.h"
#include "oslib.h"

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#endif

MainWindow::MainWindow(QString rootdir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rootdir = (new QFileInfo(rootdir))->canonicalFilePath();
    this->rootdir = rootdir;
    ui->setupUi(this);
    dirmodel = new QDirModel(ui->listView);
    QStringList strl("*");
    leftmodel = new QDirModel(strl,QDir::AllDirs | QDir::NoDotAndDotDot,QDir::Unsorted);
    ui->listView->setModel(dirmodel);
    //ui->listView->setAutoFillBackground(true);
    //ui->listView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->listView->setRootIndex(dirmodel->index(rootdir));
    ui->treeView->setModel(leftmodel);
    ui->treeView->setRootIndex(leftmodel->index(rootdir));
    this->setWindowTitle(rootdir);
    ui->lcdNumber->setVisible(false);
    ui->centralwidget->setVisible(false);
#ifdef Q_OS_WIN32
    settings = new QSettings("HKEY_CURRENT_USER\\Software\\EasternHeart\\QFileMan",QSettings::NativeFormat);
#elif defined(Q_OS_LINUX)
    settings = new QSettings("EasternHeart","QFileMan",this);
#else
#error QSettings port!!!
#endif
    {
        QVariant var = settings->value("dockWidget_visible",QVariant(true));
        var.convert(QVariant::Bool);
        ui->dockWidget->setVisible((*((const bool *)var.data())));
    }
    {
        QVariant var = settings->value("dockWidget_3_visible",QVariant(true));
        var.convert(QVariant::Bool);
        ui->dockWidget_3->setVisible((*((const bool *)var.data())));
    }
    {
        QVariant var = settings->value("dockWidget_4_visible",QVariant(true));
        var.convert(QVariant::Bool);
        ui->dockWidget_4->setVisible((*((const bool *)var.data())));
    }
}

MainWindow::~MainWindow()
{
    settings->deleteLater();
    delete ui;
}

//not used...
void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
}

void MainWindow::on_pushButton_clicked()
{
    QFileInfo fi = dirmodel->fileInfo(ui->listView->rootIndex());
    QString now = fi.canonicalFilePath();
    int last = now.lastIndexOf('/');
    now.remove(last,now.length()-last);
    if(now == "") now = "/";
    ui->listView->setRootIndex(dirmodel->index(now));
    fi = dirmodel->fileInfo(ui->listView->rootIndex());
    ui->plainTextEdit->document()->setPlainText(pathConv_o2a(rootdir,fi.canonicalFilePath()));
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QFileInfo fi = leftmodel->fileInfo(index);
    if(fi.isDir())
    {
        ui->listView->setRootIndex(dirmodel->index(fi.canonicalFilePath()));
        ui->plainTextEdit->document()->setPlainText(pathConv_o2a(rootdir,fi.canonicalFilePath()));
    }
}

//Not used...
void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QFileInfo fi = dirmodel->fileInfo(index);
    ui->lcdNumber->setVisible(false);
    if(!fi.isDir())
    {
        ui->lcdNumber->setVisible(true);
        ui->lcdNumber->display((int)fi.size());
        ui->widget->DoPreview(fi);
    }
    else
    {
        ui->widget->Clean();
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Search swin(rootdir, ui->plainTextEdit->document()->toPlainText(),arg1);
    swin.setModal(true);
    swin.exec();
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    QFileInfo fi = dirmodel->fileInfo(index);
    if(fi.isDir())
    {
        ui->listView->setRootIndex(index);
        ui->plainTextEdit->document()->setPlainText(pathConv_o2a(rootdir,fi.canonicalFilePath()));
    }
    else
    {
        osExecute(fi.canonicalFilePath());

    }
}


void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    if(this->isVisible())
    {
        settings->setValue("dockWidget_visible",visible);
    }
}

void MainWindow::on_dockWidget_3_visibilityChanged(bool visible)
{
    if(this->isVisible())
    {
        settings->setValue("dockWidget_3_visible",visible);
    }
}

void MainWindow::on_dockWidget_4_visibilityChanged(bool visible)
{
    if(this->isVisible())
    {
        settings->setValue("dockWidget_4_visible",visible);
    }
}

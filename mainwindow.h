#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QDirModel>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QString rootdir, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_comboBox_activated(const QString &arg1);

    void on_listView_activated(const QModelIndex &index);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_3_visibilityChanged(bool visible);

    void on_dockWidget_4_visibilityChanged(bool visible);

private:
    Ui::MainWindow *ui;
    QDirModel *dirmodel;
    QDirModel *leftmodel;
    QString rootdir;
    QSettings *settings;
};

#endif // MAINWINDOW_H

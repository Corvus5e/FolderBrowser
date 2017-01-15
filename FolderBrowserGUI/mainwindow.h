#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <renderarea.h>
#include <QFileSystemModel>
#include <QTreeView>

#include <foldertreebuilder.h>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();    
    void on_treeView_doubleClicked(const QModelIndex &index);
    void onTreeBuilt(fb::Folder*);

private:
    Ui::MainWindow *ui;
    RenderArea* render_area;
    QFileSystemModel *fs_model;    

    FolderTreeBuilder* builder;
};

#endif // MAINWINDOW_H

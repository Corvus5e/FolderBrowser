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

private:
    Ui::MainWindow *ui;
    RenderArea* render_area;
    QFileSystemModel *fs_model;
    QTreeView *tree;

    FolderTreeBuilder* builder;
};

#endif // MAINWINDOW_H

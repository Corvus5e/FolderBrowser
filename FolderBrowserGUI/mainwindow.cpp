#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    render_area = ui->openGLWidget;
    fs_model = new QFileSystemModel();
    fs_model->setRootPath(QDir::currentPath());
    fs_model->setFilter(QDir::Dirs);

    ui->treeView->setModel(fs_model);
    ui->treeView->setRootIndex(fs_model->index(QDir::currentPath()));

    ui->path_edit->setText(QDir::currentPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString root_path = ui->path_edit->text();
    fb::FolderTree* ft = new fb::FolderTree(root_path);

    QThread* thread = new QThread();
    ft->moveToThread(thread);

    connect(thread, SIGNAL(started()), this, SLOT(onTreeBuildStarter()));
    connect(thread, SIGNAL(started()), ft, SLOT(buildTree()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(ft, SIGNAL(ready(fb::FolderTree*)), render_area, SLOT(onTreeBuilt(fb::FolderTree*)));
    connect(ft, SIGNAL(ready(fb::FolderTree*)), this, SLOT(onTreeBuilt(fb::FolderTree*)));
    thread->start();
}

void MainWindow::onTreeBuildStarter(){
    ui->status_label->setText("building tree ...");
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path =  fs_model->fileInfo(index).absoluteFilePath();
    ui->treeView->setRootIndex(fs_model->setRootPath(path));

    ui->path_edit->setText(path);
}

void MainWindow::onTreeBuilt(fb::FolderTree *folder_tree)
{
    if(this->folder_tree != nullptr)
        delete this->folder_tree;
    this->folder_tree = folder_tree;

    unsigned long long nsize = folder_tree->getRootFolder()->size();
    ui->size_label->setText(QString::number(nsize).append(" bytes"));
    ui->status_label->setText("");
}

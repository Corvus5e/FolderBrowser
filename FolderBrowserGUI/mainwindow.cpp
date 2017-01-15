#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>

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

    if(builder != nullptr)
        delete builder;

    builder = new FolderTreeBuilder(root_path);
    connect(builder, SIGNAL(ready(fb::Folder*)), render_area, SLOT(onTreeBuilt(fb::Folder*)));
    connect(builder, SIGNAL(ready(fb::Folder*)), this, SLOT(onTreeBuilt(fb::Folder*)));
    builder->buildTree();    
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path =  fs_model->fileInfo(index).absoluteFilePath();
    ui->treeView->setRootIndex(fs_model->setRootPath(path));

    ui->path_edit->setText(path);
}

void MainWindow::onTreeBuilt(fb::Folder *folder)
{
    ui->size_label->setText(QString::number(folder->size()).append(" bytes"));
}

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

    tree = new QTreeView(ui->dir_widget);
    tree->setModel(fs_model);
    tree->setRootIndex(fs_model->index(QDir::currentPath()));
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
    builder->buildTree();
}

#include "foldertreebuilder.h"
#include <QDebug>

FolderTreeBuilder::FolderTreeBuilder(QObject *parent) : QObject(parent)
{

}

FolderTreeBuilder::FolderTreeBuilder(QString& root_path, QObject *parent) : QObject(parent)
{
    this->root = new fb::Folder(root_path.toStdString());
}

void FolderTreeBuilder::buildTree(){
    fb::buildFolderTree(this->root);
    emit this->ready(this->root);
}

const fb::Folder* FolderTreeBuilder::getRootFolder(){
    return this->root;
}

FolderTreeBuilder::~FolderTreeBuilder(){
    fb::deleteFolderTree(this->root);
    qDebug() << "FolderTreeBuilder::destructor";
}

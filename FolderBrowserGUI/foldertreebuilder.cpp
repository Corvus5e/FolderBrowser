#include "foldertreebuilder.h"

#include <QTextCodec>
#include <QDebug>

#include <iostream>

FolderTreeBuilder::FolderTreeBuilder(QObject *parent) : QObject(parent)
{

}

FolderTreeBuilder::FolderTreeBuilder(QString& root_path, QObject *parent) : QObject(parent)
{        
    setlocale( LC_ALL,"Russian");
    //std::string path = root_path.toStdString();
    QByteArray utf8 = root_path.toLocal8Bit();
    std::string path(utf8.data(), utf8.size());
    std::cout << path << std::endl;
    this->root = new fb::Folder(path);
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

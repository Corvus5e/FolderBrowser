#include "foldertree.h"

#include <QTextCodec>
#include <QDir>
#include <QDebug>

#include <iostream>

fb::FolderTree::FolderTree(QObject *parent) : QObject(parent)
{

}

fb::FolderTree::FolderTree(QString& root_path, QObject *parent) : QObject(parent)
{        
    this->root = new fb::Folder(root_path);
}

unsigned long long fb::FolderTree::recursiveBuildTree(QString &root_path, fb::Folder *root_folder)
{
    QDir dir(root_path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden | QDir::System);

    if (dir.exists()) {

        QFileInfoList sub_files = dir.entryInfoList();

        for(auto it = sub_files.begin(); it != sub_files.end(); ++it){

            QString next_path = it->filePath();

            if(it->isDir()){
                fb::Folder* node = new fb::Folder(it->fileName());
                root_folder->nodes().push_back(node);
                unsigned long long node_size = recursiveBuildTree(next_path, node);
                root_folder->setSize(root_folder->size() + node_size);
            }
            else{
                root_folder->setSize(root_folder->size() + it->size());
            }
        }
        return root_folder->size();
    }
    else {
        qDebug() << "Cannot open directory " << root_path;
        return 0;
    }

}

void fb::FolderTree::buildTree(){
    recursiveBuildTree(root->name(), root);
    emit this->ready(this);
}

const fb::Folder* fb::FolderTree::getRootFolder(){
    return this->root;
}

void fb::FolderTree::deleteTree(fb::Folder *root)
{
    if(root->nodes().size() > 0){
        for(auto it = root->nodes().begin(); it != root->nodes().end(); ++it){
            deleteTree(*it);
        }
    }
    delete root;
}

fb::FolderTree::~FolderTree()
{
    deleteTree(this->root);
    qDebug() << "FolderTree::destructor";
}

#ifndef FOLDERTREEBUILDER_H
#define FOLDERTREEBUILDER_H

#include <QObject>
#include <folder_browser.h>

class FolderTreeBuilder : public QObject
{
    Q_OBJECT

private:
    fb::Folder *root;

public:

    explicit FolderTreeBuilder(QObject *parent = 0);

    FolderTreeBuilder(QString& root_path, QObject *parent = 0);

    const fb::Folder* getRootFolder();

    ~FolderTreeBuilder();

public slots:

    void buildTree();

signals:

    void ready(fb::Folder* new_root);
};

#endif // FOLDERTREEBUILDER_H

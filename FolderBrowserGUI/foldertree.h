#ifndef FOLDERTREE_H
#define FOLDERTREE_H

#include <QObject>

namespace fb {

    class Folder {
        QString name_;
        unsigned long long size_;
        std::vector<Folder*> nodes_;

    public:

        Folder(QString& name, unsigned long long size = 0) : name_(name), size_(size){ }

        QString& name() {
            return this->name_;
        }

        std::vector<Folder*>& nodes(){
            return this->nodes_;
        }

        const std::vector<Folder*>& cnodes() const {
            return this->nodes_;
        }

        unsigned long long size() const{
            return this->size_;
        }

        void setSize(unsigned long long size) {
            size_ = size;
        }
    };

    class FolderTree : public QObject
    {
        Q_OBJECT

    private:

        fb::Folder *root;

        unsigned long long recursiveBuildTree(QString &root_path, fb::Folder *root_folder);

        void deleteTree(fb::Folder* root);

    public:

        explicit FolderTree(QObject *parent = 0);

        FolderTree(QString& root_path, QObject *parent = 0);

        const fb::Folder* getRootFolder();

        ~FolderTree();

    public slots:

        void buildTree();

    signals:

        void ready(fb::FolderTree*);
    };
}
#endif // FolderTree_H

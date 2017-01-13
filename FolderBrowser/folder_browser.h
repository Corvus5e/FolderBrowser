#ifndef FOLDER_BROWSER_H
#define FOLDER_BROWSER_H

#include <string>
#include <vector>

namespace fb { //folder browser

    class Folder {
        std::string name_;
        unsigned long long size_;
        std::vector<Folder*> nodes_;

    public:

        Folder(std::string& name, unsigned long long size = 0) : name_(name), size_(size){ }

        std::string& name() {
            return this->name_;
        }

        std::vector<Folder*>& nodes(){
            return this->nodes_;
        }

        unsigned long long size(){
            return this->size_;
        }

        void setSize(unsigned long long size) {
            size_ = size;
        }
    };

    void buildFolderTree(fb::Folder *root_folder);

    void deleteFolderTree(fb::Folder *root_folder);

    unsigned long fileSize(std::string& path);
}

#endif // FOLDER_BROWSER_H


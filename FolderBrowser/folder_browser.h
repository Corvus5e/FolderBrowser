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

        void setName(std::string& name){
            this->name_ = name;
        }

        std::vector<Folder*>& nodes(){
            return this->nodes_;
        }

        std::string& name() {
            return this->name_;
        }

        unsigned long long& size(){
            return this->size_;
        }
    };

    void buildFolderTree(std::string& root_path, fb::Folder *root_folder);
}

#endif // FOLDER_BROWSER_H



#include <folder_browser.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

namespace {

    void fullPath(std::string& root, std::string& node, std::string& full_path)
    {
        full_path = root;
        full_path.append("\\");
        full_path.append(node);
    }

    unsigned long long recursiveBuildTree(std::string &root_path, fb::Folder *root_folder)
    {
        DIR *dir;
        struct dirent *ent;

        dir = opendir (root_path.c_str());
        if (dir != NULL) {

            while ((ent = readdir (dir)) != NULL) {

                std::string next_path;
                fullPath(root_path, std::string(ent->d_name), next_path);

                if(ent->d_type == DT_DIR){

                    if(strcmp(".", ent->d_name) && strcmp("..", ent->d_name)){
                        fb::Folder* node = new fb::Folder(std::string(ent->d_name));
                        root_folder->nodes().push_back(node);

                        unsigned long long node_size = recursiveBuildTree(next_path, node);
                        root_folder->setSize(root_folder->size() + node_size);
                    }
                }
                else{
                    root_folder->setSize(root_folder->size() + fb::fileSize(next_path));
                }
            }

            closedir (dir);
            return root_folder->size();
        }
        else {
            printf ("Cannot open directory %s\n", root_path.c_str());
            return 0;
        }

    }
}

void fb::buildFolderTree(fb::Folder *root_folder)
{
    recursiveBuildTree(root_folder->name(), root_folder);
}

void fb::deleteFolderTree(fb::Folder *root_folder){
    if(root_folder->nodes().size() > 0){
        for(auto it = root_folder->nodes().begin(); it != root_folder->nodes().end(); ++it){
            deleteFolderTree(*it);
        }
    }
    delete root_folder;
}

unsigned long fb::fileSize(std::string &path){
    struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}


#include <folder_browser.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

void fb::buildFolderTree(std::string &root_path, fb::Folder *root_folder)
{
    DIR *dir;
    struct dirent *ent;

    dir = opendir (root_path.c_str());
    if (dir != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            if(ent->d_type == DT_DIR){

                if(strcmp(".", ent->d_name) && strcmp("..", ent->d_name)){
                    Folder* node = new Folder();
                    node->setName(std::string(ent->d_name));
                    root_folder->nodes().push_back(node);

                    std::string next_path(root_path);
                    next_path.append("\\");
                    next_path.append(node->name());

                    fb::buildFolderTree(next_path, node);
                }
            }
            else{

            }
        }

        closedir (dir);

    } else {
        printf ("Cannot open directory %s\n", root_path.c_str());
    }
}

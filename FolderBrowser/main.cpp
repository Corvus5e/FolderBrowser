#include <iostream>
#include <folder_browser.h>
#include <iomanip>

using namespace std;
using namespace fb;

void printTree(Folder* root, int level = 0)
{
    cout << string(level, '-') << root->name() << endl;
    for(auto i = 0; i < root->nodes().size(); i++){
        printTree(root->nodes().at(i), level + 4);
    }
}

int main(int argc, char *argv[])
{
    std::string root_path(argc > 1 ? argv[1] : ".");
    //std::string root_path("D:\\Labs\\My\\FolderBrowser\\build-FolderBrowser-Desktop_Qt_5_5_1_MSVC2010_32bit-Debug");
    fb::Folder* rf = new fb::Folder();
    rf->setName(root_path);

    fb::buildFolderTree(root_path, rf);
    printTree(rf);
    return EXIT_SUCCESS;
}



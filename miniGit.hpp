#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <string>

//#include <filesystem>
//namespace fs = std::filesystem;

using namespace std;

struct singlyNode{
    std::string fileName; // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};
struct doublyNode{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};
class miniGit{
    public:
        void Addfile();
        void Removefile();
        void Commit();
        void Checkout(int com);
    
    private:
        doublyNode *root;
        doublyNode *current;
};

//fs::remove_all(".minigit"); // removes a directory and its contents
//fs::create_directory(".minigit"); // create a new directory
#endif
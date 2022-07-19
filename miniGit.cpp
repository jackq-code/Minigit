//#include <filesystem>

#include <iostream>

#include <fstream>

#include <sstream>
#include <string.h>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
//namespace fs = std::filesystem;
//using namespace std::experimental::filesystem::v1;
using namespace std;

miniGit::miniGit(){
    fs::create_directory(".minigit"); // create a new directory
    current = root;
    doublyNode* adder = new doublyNode;
	root = adder;
	adder->next =NULL;
    current = root;
    adder->commitNumber = 0;
	return;
}
miniGit::~miniGit(){
    doublyNode* curr = root;
    doublyNode* currDel = root;
    while(curr!=NULL){
        singlyNode * pos = curr->head;
        singlyNode * posDel = curr->head;
        while(pos!=NULL){
            posDel = pos;
            pos = pos->next;
            delete posDel;
            posDel = NULL;
        }
        currDel = curr;
        curr = curr->next;
        delete currDel;
        currDel = NULL;
    }
    fs::remove_all(".minigit"); // removes a directory and its contents
    return;
}
bool findCommit(int j){
    doublyNode* curr = root;
    while(curr!=NULL){
        if(curr->next == NULL && j == curr->commitNumber){
            return true;
        }
        curr = curr->next;
    }
    return false;
}
void miniGit::Addfile(){
    if(!findCommit(current->commitNumber)){
        cout << "In wrong commit, cannot procede" << endl;
        return;
    }
    bool found = false;
    While(found == false){
    Cout << "Write a filename" << endl;
	string File;
    getline(cin, File);
    //std::string filename = 'test00.txt';
    if(fs::exists(File)){
         
    }
    else{
        found = true;
        //ifstream File;
        singlyNode * curr = current->head;
        while(curr!= NULL){
            if(curr->fileName == File){
                cout << "File already exists" << endl;
                return;
            }
            if(curr->next == NULL){
                string a = File.substr(0,File.length()-6);
                string b = File.substr(File.length()-5,File.length()-1);
                string c = "00" + File;
                singlyNode* adder = new singlyNode;
                adder->fileName = File;
                //adder->fileVersion = c;
                curr->next = adder;
                return;
            }
            curr = curr->next;
        }

    }
    }
    return;

}
bool changed(string file, string changed){
    ifstream dataFile;
    ifstream changedFile;
	string dataLine;
    string dataLine2;
    dataFile.open(file);
    changedFile.open(changed);
    while (getline(dataFile, dataLine)){
        getline(changedFile ,dataLine2);
        if(dataLine != dataLine2){
            return true;
        }
    }
    dataFile.close();
    changedFile.close();
    return false;
}
void writeOver(string from, string to){
    ifstream dataFile;
    ofstream changedFile;
	string dataLine;
    string dataLine2;
    dataFile.open(from);
    changedFile.open(to);
    while (getline(dataFile, dataLine)){
        changedFile << dataLine << endl;
    }
    dataFile.close();
    changedFile.close();
    return;
}
void miniGit::Removefile(){
    if(!findCommit(current->commitNumber)){
        cout << "In wrong commit, cannot procede" << endl;
        return;
    }
    Cout << "Write a filename" << endl;
	string File;
    bool exist = false;
    getline(cin, File);
    //std::string filename = 'test00.txt';
    singlyNode * curr = current->head;
    singlyNode * prev = current->head;
        while(curr!= NULL){
            if(curr->fileName == File){
                exist = true;
                if(curr == current->head){
                    current->head = NULL;
                    delete curr;
                    curr = NULL;
                }
                else{
                    prev->next = curr->next;
                    delete curr;
                    curr = NULL;
                }
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    if(exist == false){
        Cout << "File not Found" << endl;
    }
    return;
}
void miniGit::Commit(){
    if(!findCommit(current->commitNumber)){
        cout << "In wrong commit, cannot procede" << endl;
        return;
    }
    doublyNode* adder = new doublyNode;
    singlyNode* curr1 = new singlyNode;
    singlyNode * curr1 = current->head;
    singlyNode * curr = current->head;
    adder->head = curr1;
    curr2 = adder->head;
    singlyNode* prev;
    while(curr!= NULL){
        singlyNode* adderino = new singlyNode;
        adderino->fileName = curr->fileName;
        if(fs::exists(curr->fileVersion)){
            if(changed(adderino->fileName,curr->fileVersion)){
                string a = adderino->fileName;
                string b = a.substr(0,1);
                int conver = stoi(b);
                conver++;
                if(conver<10){
                    b = "0" + to_string(conver);
                }
                string c = b + adderino->fileName;
                adderino->fileVersion = c;
                writeOver(adderino->fileName, adderino->fileVersion);
            }
        }
        else{
            string c = "00" + adderino->fileName;
            adderino->fileVersion = c;
            writeOver(adderino->fileName, adderino->fileVersion);
        }
        prev->next = adderino;
        prev = adderino;
        curr = curr->next;
    }
    doublyNide* temp = root;
    doublyNide* temp2 = root;
    while(temp!=NULL){
        if(temp->next ==NULL){
             temp2=temp;
        }
        temp = temp->next;
    }
    current = temp2;
    adder->previous = temp2;
    temp2->next = adder;
    adder->commitNumber = temp2++;
    return;
}
void miniGit::Checkout(int com){
    doublyNide* temp = root;
    doublyNide* store = NULL;
    while(temp!=NULL){
        if(temp->commitNumber ==com){
             store = temp;
        }
        temp = temp->next;
    }
    if(store == NULL){
        cout << "Invalid commit number" << endl;
        return;
    }
    singlyNode * curr = store->head;
    current = store;
    while(curr!= NULL){
        writeOver(curr->fileVersion, curr->fileName);
        curr = curr->next;
    }
    return;
}


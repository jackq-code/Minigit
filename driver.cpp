
#include <iostream>

#include <fstream>

#include <sstream>

#include "miniGit.hpp"
using namespace std;



int main(int argc, char *argv[])
{
    //fs::create_directory(".minigit");
	
	bool quit = false;
	while (!quit)
	{
		int option;
		string inputLine;
        miniGit git;
		cout << "======Main Menu======" << endl;
		cout << "1. Add file to the current commit" << endl;
		cout << "2. Remove file from the current commit" << endl;
        cout << "3. Commit changes" << endl;
        cout << "4. Check out a specific version based on a unique commit number" << endl;
		cout << "5. Quit" << endl;

		getline(cin, inputLine);

		if (inputLine.length() != 1 || inputLine[0] < '0'
			|| inputLine[1] > '4') {
			cerr << "Invalid option : " << inputLine << endl;
			continue;
		}

		option = stoi(inputLine);

		switch (option)
		{

			case 1:
			{
				git.Addfile();
				break;
			}
			case 2:
			{
				git.Removefile();
				break;
			}
	    case 3:
			{
	      		git.Commit();

	      break;
			}
            case 4:
            {
                cout<< "give the commit number"<<endl;
				string nodename;
				getline(cin, nodename);
                if(stoi(nodename) > 0){
                    git.Checkout(stoi(nodename));
                }
                else{
                    cout << "Invalid commit number" << endl;
                }
                break;
            }
			case 5:
			{
				quit = true;
			}
	}
}

	cout << "Goodbye!" << endl;

	return 0;
}

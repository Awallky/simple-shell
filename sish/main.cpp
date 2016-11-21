#include <iostream>
#include <fstream>
#include <vector>
#include "sish_global.h"
#include <signal.h>
#include <stdlib.h>

vector <int> runningProcs;
string defaultPrompt = "sish >";
using namespace std;

int main(int argc, char **argv)
{
    variableList A;
    init(A);
    vector<vector<string> > in;
    string commandUsed;
    bool done = false;
    while(1)
    {
        cout << defaultPrompt << "\t";
        in = doScan(argc, argv, A);

        for(unsigned i = 0; i < in.size(); i += 1)
        {
            parse(in[i], commandUsed, A, done);
        }
        if(done)
        {
            break;
        }
    }
    return 0;
}

//Initializes PATH and ShowTokens variables
void init(variableList &A)
{
	listnode* newNode1 = new listnode("PATH", DEFAULTPATH, NULL);
	listnode* newNode2 = new listnode("ShowTokens", "0", NULL);
	A.insertVar(newNode1);
	A.insertVar(newNode2);
}

//prints the contents of a vector
void printVec(vector<string> vec)
{
	for( unsigned i = 0; i < vec.size(); i += 1 )
	  {
	  	cout << vec[i] << endl;
	  }
}

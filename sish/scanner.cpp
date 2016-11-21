#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "sish_global.h"

extern string defaultPrompt;

vector<string> getTokens(char* argv, variableList &A)
{
    vector<string> tokens;
    stringstream stream;
    string buf;

    std::ifstream iFile(argv);
    /* protect against bad file names */
    if(iFile.fail())
    {
      return tokens;
    }
    /* reads tokens in from each line in
       the file delimited by whitespace */
    char *char_buf = 0; // NULL
    iFile.seekg(0,std::ios_base::end); // look for the end of the file
    int file_size = iFile.tellg(); // get the size of the file in bytes
    iFile.seekg(0,std::ios_base::beg); // return pointer to the beginning of the file
    char_buf = new char[file_size+2]; //allocate enough space in the buffer for the file
    char_buf[file_size+1] = '\0'; // mark end of string just in case
    iFile.read(char_buf,file_size); // read file contents into the buffer
    stream << char_buf; //cast as sstream data type
    delete char_buf;

    while(getline(stream, buf, ' ') )
    {
        tokens.push_back(buf); // store tokens delimited by whitespace
    }

    print(tokens);
    iFile.close();
    return tokens;
}


vector<vector<string> >doScan(int argc, char** argv, variableList &A)
{
     vector<vector<string> > tokens;//holds each file's tokens

    /* If command line text files are provided
       try to open them */
    if(argc > 1)
    {
        int i = 0;
        /* get each command line argv's file contents */
        while(i < argc)
        {
            vector <string> tok = getTokens(argv[i], A);
            if( !tok.empty())
            {
                tokens.push_back(tok);
            }
            else
            {
                cout << "Error. Unable to open file." << endl;
            }
            i += 1;
            bool found;
            if(A.findd("ShowTokens", found) == "1")
            {
               print(tok);
            }
        }

        return tokens;
    }
    else
    {
        std::string tok, buf;
        getline(std::cin,buf);
	if (cin.eof())
	  {
		exit(0);
	  }
        std::stringstream uIn(buf);
        vector<string> tokenVector;

        while(uIn >> tok)
        {
            tokenVector.push_back(tok);
        }
        tokens.push_back(tokenVector);
        bool found;
        if(A.findd("ShowTokens", found) == "1")
        {
            print(tokenVector);
        }
    }

    return tokens;
}

void print(vector<string> tokens)
{
    for(unsigned i = 0; i < tokens.size(); i += 1)
    {
        cout << tokens[i] << "\n";
    }
    cout << endl;
}

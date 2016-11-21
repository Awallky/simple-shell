#include <iostream>
#include <string>
#include <unistd.h> //fork
#include <sys/types.h> // waitpid, wait
#include <cstdlib>
#include <stdio.h>
#include "sish_global.h"
#include "variableList.h"
#include <sys/wait.h> //waitpid, wait
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <signal.h>

extern string defaultPrompt;
extern vector <int> runningProcs;

void runSishCommand(vector<string> tok, string commandUsed, variableList& A)
{
    string args;
    if(commandUsed == "%" )
    {
        return;
    }
    if(commandUsed == "listprocs" )
    {
	cout << "----------- Background Processes in Sish ----------\n";
	if (runningProcs.empty())
	  {
		return;
	  }

	for (unsigned i = 0; i < runningProcs.size(); i++)
	  {
		cout << runningProcs[i] << endl;
	  }

        return;
    }
    else if(commandUsed == "set" )
    {
        // if the first and last characters of the last token
        // are not parentheses
        if( !(tok[2][0] == '"' &&
              tok[tok.size()-1][tok[tok.size()-1].size()-1] == '"' ) )
        {
            cout << "Invalid set phrase. Need open and closed quotations.\n";
            return;//invalid set phrase
        }

        //run sish command for every variable listed
        //for(int i = 1; i < tok.size()-1; i += 1)
        //{
            doSetCommand( tok[1], tok[2], A );
        //}
    }
    else if(commandUsed == "defprompt" )
    {
        string temp;
        for(unsigned i = 1; i < tok.size(); i += 1)
        {
            temp += tok[i];
            temp += " ";
        }
        doDefpromptCommand(temp, A);
    }
    else if(commandUsed == "cd" )
    {
        doCDCommand(tok[1], A);
    }
    /* END OF BUILT IN COMMANDS */

    /* BEGIN OF UNIX COMMANDS */
    else if(commandUsed == "run" )
    {
        doRunCommand(tok, A);
    }
    else if(commandUsed == "assignto" )
    {
        doAssignToCommand(tok, A);
    }
    /* END OF UNIX COMMANDS */
    else
    {
        cout << "Error. Invalid statement. You broke my sish shell." << endl;
        return;
    }
}

void doSetCommand(string variable, string value, variableList& A)
{
    A.lookupVar(variable, value);
    return;
}


void doDefpromptCommand(string argument, variableList& A)
{
    defaultPrompt = argument;
    return;
}


void doCDCommand(string argument, variableList& A)
{
    chdir(argument.c_str());
    return;
}


void doRunCommand(vector<string> tok, variableList& A)
{
    pid_t pid = fork();
    bool found = false;

    if (pid < 0)
	{
          printf("fork() failed!\n");
	}

   // Child process executes the approriate command
    else if (pid == 0)
    {
	//patch until a better fix is found
	if(tok[tok.size()-1] == "&" && tok[1] == "./sish")
	{
		tok.pop_back();
	}

       char* temp[tok.size()];
       for (unsigned i =0; i < tok.size()-1; i ++)
         {
	   if (tok[i+1][0] == '$')
	    {
	      string tempval = A.findd(tok[i+1].substr(1,tok[i+1].size() - 1), found);

              if( found == true )
	       {
	         tok[i+1] = tempval;
               }
	    }
		  temp[i] = (char*) tok[i+1].c_str();
         }
       temp[tok.size()-1] = NULL;

	    //setenv(const char* name, const char* value, int overwrite);
       string str = A.findd("PATH", found);
       char* PATH = (char*) str.c_str();
       if( tok[1][0] == '/' )
        {
          setenv( "PATH",  PATH, 1);
        }
       execvp(temp[0], temp);
       if( tok[1][0] == '/' )
         {
           unsetenv("PATH");
         }

	    //unsetenv(const char* name);
       printf("Execvp failed!\n");
       exit(1);

    }

    // This is the code for the parent
    else
    {
	//when the child returns, the parent's background process is finished
	signal(SIGCHLD, backgroundHandler);
        // if we don't see an ampersand, we must wait for child to finish
        if( (tok[tok.size()-1] != "&") )
        {
	   waitpid(pid, NULL, 0); // make the process wait if neccessary
        }

        // Else it should run in background add to the list of currently running processes
        else
        {
         runningProcs.push_back(pid);   // We should push the PID to a vector of PIDs THIS NEEDS TO BE ADDED
        }
    }
    return;
}


void backgroundHandler(int sig)
{
	if(runningProcs.empty())
	{
		return;
	}
	else
	{
		runningProcs.pop_back();
	}
}


void doAssignToCommand(vector<string> tok, variableList& A)
{
    pid_t pid = fork();
    bool found = false;
    int count;
    char c;

    if (pid < 0)
	{
          printf("fork() failed!\n");
	}

   // Child process executes the approriate command
    else if (pid == 0)
    {
        char* temp[tok.size()];
        for (unsigned i =0; i < tok.size()-2; i ++)
        {
		// Checks to see if they are calling a variable that has been assigned
		if (tok[i+1][0] == '$')
		{
			// This would replace the $var with its value
			string tempval = A.findd(tok[i+2].substr(1,tok[i+2].size() - 1), found);
			if( found == true )
		  	{
		    		tok[i+2] = tempval;
	  	  	}
		}
		temp[i] = (char*) tok[i+2].c_str();
        }
	temp[tok.size()-2] = NULL;

	// Forked child will close its standard output and open a temporary file to write to
	close(1);
	open ("/tmp/tempfile1.txt", O_WRONLY|O_TRUNC|O_CREAT,0666); // creates the file if needed, truncates it to zero, and writeable.
        execvp(temp[0], temp);
        printf("Execvp failed!\n");
        exit(1);
    }
    // This is the code for the parent
    else
    {
	// Wait for the child process to finish before executing any commands
	waitpid(pid,NULL, 0);

	// open the file we created in the child
	FILE* fd = fopen("/tmp/tempfile1.txt", "r");
    	char char_buf[255]; // NULL

    	string variable_string_value = "";
    	while ( fgets( char_buf, 255, fd) )
    	{
		variable_string_value.append(char_buf);
    	}
    	variable_string_value.append(char_buf);
    	doSetCommand( tok[1], variable_string_value, A);

        fclose (fd);
     }
     return;
}


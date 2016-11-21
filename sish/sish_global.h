#ifndef SISH_GLOBAL_H_INCLUDED
#define SISH_GLOBAL_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "variableList.h"
#include <signal.h>
#include <stdio.h>
using namespace std;

/* ======================================= */
//Initialize ShowTokens variable in list
#define DEFAULTPATH "/bin:/usr/bin/"
void init(variableList &A);
//END OF INIT FUNCTION DEFS


//Scanner definitions
vector <string> getTokens(char* argv, variableList &A);
vector <vector <string> > doScan(int argc, char** argv, variableList &A);
void print(vector<string> tokens);
//End of Scanner definitions

/* ======================================= */

//Parser definitions
void parse(vector<string> tok, string &commandUsed, variableList& A, bool &done);
void set_defprompt(string newPrompt);
vector<string> parseLines( vector<string> tokens);
//End of Parser Definitions

/* ======================================= */

//Sish Commands definitions
void runSishCommand(vector<string> tok, string commandUsed, variableList& A);
void doListprocsCommand(string argument, variableList& A);
void doSetCommand(string variable, string value, variableList& A);
void doDefpromptCommand(string argument, variableList& A);
void doCDCommand(string arguments, variableList& A);
//End of built-in sish commands

//========================================

//Beginning of program control commands
void doRunCommand(vector<string> tok, variableList& A);
void backgroundHandler(int sig);
void doAssignToCommand(vector<string> tok, variableList& A);
//End of Sish Command definitions

void printVec(vector<string> vec);

/* ======================================= */

#endif // SISH_GLOBAL_H_INCLUDED

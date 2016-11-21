#include "sish_global.h"
extern string defaultPrompt;

/* Returns whether the string contains an acceptable instr. */
/* Also changes the command used variable to the appropriate keyword */

void parse(vector <string> tok, string& commandUsed, variableList& A, bool &done)
{
  if( tok.empty() ){
      //cout << "Empty input list.\n";
      return;
  }
  else if(tok[0][0] == '%'){
	return;
  }
  else if(tok[0] == "cd"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
	return;
  }
  else if(tok[0] == "defprompt"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
    return;
  }
  else if(tok[0] == "set"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
    return;
  }
  else if(tok[0] == "listprocs"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
	return;
  }
  else if(tok[0] == "run"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
	return;
  }
  else if(tok[0] == "assignto"){
    commandUsed = tok[0];
    runSishCommand(tok, commandUsed, A);
	return;
  }
  else if(tok[0] == "done")
  {
      cout << "Exiting...\n";
      done = true;
  }
  else{
	cout << "Oops. You've entered an invalid phrase.\n";
	return;
  }

}

void set_defprompt(string newPrompt)
{
	defaultPrompt = newPrompt;
	return;
}

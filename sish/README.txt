Files: main.cpp sish_commands.cpp scanner.cpp parser.cpp variableList.cpp variableList.h sish_global.h

Member Names: Adam Walls, Clay Marshall 

Description of Algorithms:

-The implemetation files rely on two global header files:
 sish_global.h and variableList.h

-main.cpp:
	main initializes the PATH and ShowTokens variables
	and then enters a loop until "done" is typed or the user enters <ctrl-d>
	it calls the scanner, which handles user file and keyboard input

-scanner.cpp:
	checks whether the user has entered any files as input
	or if they are using keyboard input

	For the file input, it reads the size of each file,
	fills a buffer large enough to hold the file contents,
	and then tokenizes the input using a strignstream object, 
	filling a vector of strings
	
	It then returns the vector to main, wwhich calls the parser

-parser.cpp:
	parser checks to see if the first token of each input line is
	one of the following:
	
	1) if the first character of the first token is '%', it returns
	   since that represents a comment and can be disregarded 
	2) if the first token is either "cd", "defprompt", "set", 
	   "listprocs", "run", or "assignto", it calls the 
	   runSishCommand function

-runSishCommand.cpp:
	1) if the first token is "cd", it calls the chdir command
	2) if the first token is "defprompt", it re-assigns the default
	   prompt to the newly defined prompt
	3) if it is "set", then it looks for the variable name, 
	   and changes the value if the variable exists in the linked list,
	   or appends it to the list if it is a new variable
	   However, it will not allow a set command if the value is not
	   enclosed in double quotes
	4) If it is "listprocs" it displays a vector of pids from
	   when a parent process waited for a child to execute and 
	   the child displayed its parent's pid
	5) If it is "run", the shell looks to see if the last token is
	   "&" and is sent to the background, and allows the user to issue
	   another command
	   If not, then it immediately executes the command
	6) If it is "assgnto", the parent process forks, the
	   child process closes fd1, the standard out file descriptor,
	   opens a temp file as readable and writeable by all, 
	   executes the command, and returns.
	   The parent then reads the temp file's contents into
	   a stringstream object and places its contents into
	   string variable, which is then placed into the variableList
	   It then closes the file descriptor

-variableList.cpp:
	-A linked list that adds variables to the end of the list
	-Can search and return values if a variable name is in the list
	-Searches for variables and replaces their value if found in set calls
	 or appends them to the end of the list if it is not found.

-BUGS:
	One bug found before the pathc is when 
	run ./sish & 
	is run, causing the program to crash. So, the program ignores the & when this is run

	There are certain cases that omit the first character of an assignto call.

#ifndef VARIABLELIST_H
#define VARIABLELIST_H
#include <string>
using namespace std;

struct listnode{
	std::string var_name;
	std::string string_value;
	int int_value;
	listnode* nextNode;

	listnode(std::string name, std::string str_val, listnode* next);
	listnode* getNextNode(listnode* curr) const;
	std::string getVarName() const;
	int getVarValAsInt() const;
	std::string getVarValAsString() const;

};

class variableList{
   private:
	listnode* head;//thinking about making this a vector of listnodes
//	static string defaultPrompt = "sish >"; // The Default Prompt that is output
   public:
	variableList(); //constructor
	~variableList();//destructor
	void lookupVar(std::string varName, string value);
	void deleteVar(std::string name);//looks for var name and deletes if found
	void printVariableList();
	void insertVar(listnode* var);
	string findd(string varName, bool &found);//looks for variable name and returns if found
	//add member functions
	// vector <int> runningProcs;
};
/* May or may not use this */
class hashTable{
   private:
	std::vector <variableList> list;
   public:
};
#endif


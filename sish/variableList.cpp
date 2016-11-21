#include <iostream>
#include <vector>
#include <string>
#include "variableList.h"

/* listnode class members */
//========================================================
/* listnode constructor */
listnode::listnode(string name, string token, listnode* next)
{
   this->var_name = name;
//   this->int_value = tok;
   this->string_value = token;
   this->nextNode = next;
}

std::string listnode::getVarName() const
{
   return var_name;
}

int listnode::getVarValAsInt() const
{
   return int_value;
}

std::string listnode::getVarValAsString() const
{
   return string_value;
}

listnode* listnode::getNextNode(listnode* curr) const
{
	return curr->nextNode;
}
/* End of listnode class members */
//========================================================
/* variableList class members */

//variableList constructor
variableList::variableList()
{
   head = NULL;
}

//variableList destructor
variableList::~variableList()
{
   listnode* currNode = head;
   listnode* next = NULL;

   while( currNode != NULL )
     {
       next = currNode;
       currNode = currNode->nextNode;
       delete next;
     }
     //head = 0;
}


void variableList::deleteVar(string name)
{
   listnode* prevNode = NULL;
   listnode* currNode = head;

   while( currNode != NULL  && currNode->var_name != name)
     {
       prevNode = currNode;
       currNode = currNode->nextNode;
     }
   if( currNode->var_name == name)
     {
        prevNode->nextNode = currNode->nextNode;
        delete currNode;
     }
   else
     {
        cout << "The variable to be deleted was not found\n";
     }
}


void variableList::lookupVar(string varName, string value)
{
   listnode* prevNode = NULL;
   listnode* currNode = head;
   listnode* newNode;

   if (value.size() > 2)
	value = value.substr(1, value.size()-2);

   while( currNode != NULL )
     {
        prevNode = currNode;
        currNode = currNode->nextNode;
     }

   if( head == NULL )
     {
        newNode = new listnode(varName, value, NULL);
        head = newNode;
        return;
     }
   else if( head != NULL )
   {
       if(prevNode->var_name == varName)
       {
           prevNode->string_value = value;
       }
       else
       {
           newNode = new listnode(varName, value, NULL);
           prevNode->nextNode = newNode;
       }
   }
   else
    ;
}


void variableList::insertVar(listnode* var)
{
   listnode* prevNode = NULL;
   listnode* currNode = head;
   if( currNode == NULL )
     {
        head = var;
     }
   else
     {
        while( currNode != NULL )
          {
             prevNode = currNode;
             currNode = currNode->nextNode;
          }
        prevNode->nextNode = var;
     }
}



void variableList::printVariableList()
{
   listnode* currNode = head;
   while(currNode != NULL)
     {
        cout << "Variable Name:\t" << currNode->var_name;
        cout << "\t\tValue:\t" << currNode->string_value << endl;
        currNode = currNode->nextNode;
     }
}

string variableList::findd(string varName, bool &found)
{
	listnode* currNode = head;
	listnode* prevNode = NULL;
	int i = 0;
	// printVariableList();
	while( currNode != NULL )
	  {
	//    cout << i++ << endl;
	    prevNode = currNode;
	    if (prevNode->var_name == varName)
		break;
	    currNode = currNode->nextNode;
	  }
	if( prevNode != NULL )
	  {
	    if( prevNode->var_name == varName )
	      {
		found = true;
		return prevNode->string_value;
	      }
	    else
	      {
		found = false;
	   	return "";
	      }
	  }
	else if( prevNode == NULL )
	  {
	    found = false;
	    return "";
	  }
	else
	  {
	    found = true;
	    return "";
	  }
}
/* End of variableList class members */
//========================================================
/* Beginning of hash table class members (if needed ) */



/* End of hash table class members (if needed ) */

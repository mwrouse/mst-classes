/*
	Program......: Assignment 3
	File.........: InvalidSyntaxException.h
	Student......: Michael Rouse
	Student ID...: 
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-11-11
	Description..: Recursive Descent Parser
*/
#ifndef INVALID_SYNTAX_EXCEPTION
#define INVALID_SYNTAX_EXCEPTION

#include <iostream>
#include <string>

using namespace std;

class InvalidSyntaxException
{
public:
  InvalidSyntaxException()
  {
    message = "INVALID!";
  }
  InvalidSyntaxException(string msg)
  {
    message = msg;
  }
  string what()
  {
    return message;
  }


private:
  string message;
};



#endif

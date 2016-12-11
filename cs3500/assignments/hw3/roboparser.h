/*
	Program......: Assignment 3
	File.........: roboparser.h
	Student......: Michael Rouse
	Student ID...: =
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-11-11
	Description..: Recursive Descent Parser
*/
#ifndef ROBOPARSER_H
#define ROBOPARSER_H
#include <string>
#include "InvalidSyntaxException.h"

//#define DEBUG



// Constants used for output
#define INVALID "INVALID!"
#define CORRECT "CORRECT"

#define DoNotConsumeToken false


/**
 * GLobal variables/functions needed for a RDP
 */
 extern std::string token; // Global variable
void get_token();   // Function to consume a token into the token variable
bool token_exist(); // Returns true if there are more characters in the input

/**
 * Token Identification
 */
bool IsInteger();
bool IsDecimal();
bool IsKeyword();
bool IsIdentifier();
bool IsRelation();      // < | > | = | #
bool IsAddOperator();   // + | - | "or"
bool IsMultOperator();  // * | / | "and"

bool IsStatement();
bool IsStatementSequence();
bool IsSimpleExpression();
bool IsTerm();
bool IsFactor();
bool IsExpression();
bool IsAssignment();
bool IsIfStatement();
bool IsLoopStatement();
bool IsForwardStatement();
bool IsRotateStatement();




/**
 * Functions for recognition
 *
 * These will throw InvalidSyntaxException if syntax is invalid
 */
void IsRoutineSequence(); // Start symbol
void IsRoutineDeclaration();




/**
 * Checks if a string is in an array of strings
 */
bool IsInArray(std::string inp, std::string arr[], short size)
{
  for ( unsigned short i = 0; i < size; i++ )
  {
    if ( inp.compare(arr[i]) == 0 )
      return true; // Match found!
  }

  return false;
}


void debug(string msg)
{
  #ifdef DEBUG
  cout << msg << endl;
  #endif
  msg = "";
}


void debug(string msg, bool result)
{
  if ( result )
    debug(msg + " true");
  else
    debug(msg + " false");
}


#endif

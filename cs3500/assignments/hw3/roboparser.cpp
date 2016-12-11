/*
	Program......: Assignment 3
	File.........: roboparser.cpp
	Student......: Michael Rouse
	Student ID...: 12442296
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-11-11
	Description..: Recursive Descent Parser
*/
#include <iostream>
#include <ctype.h>
#include <cstdio>
#include <string>
#include "roboparser.h"
#include "InvalidSyntaxException.h"

using namespace std;




string token;


/**
 * Main Program
 */
int main()
{

  try
  {
    do
    {
      get_token(); // Initialize token variable

      if (cin.fail())
        break;

      // Begin recognition
      IsRoutineSequence();
      debug("\t\tFinished with one prog");
    } while ( token_exist() );

    cout << CORRECT << endl; // Input was accepted

  }
  catch (InvalidSyntaxException e)
  {
    // Input was not accepted
    cout << INVALID << endl;

    #ifdef DEBUG
      cout << "Last read token: " << token << endl;
      cout << "Error: " << e.what() << endl;
    #endif
  }

  return 0;
}



/**
 * Determines if input is the start symbol
 */
void IsRoutineSequence ()
{
  IsRoutineDeclaration();
} // End IsRoutineSequence



/**
 * Determins if something is a routine declaration
 *
 * prog IDENTIFIER blip [StatementSequence] blorp
 */
void IsRoutineDeclaration ()
{
  if ( token.compare("prog") != 0 )
    throw InvalidSyntaxException("Expected 'prog' to start Routine Declaration");

  get_token(); // Consume another token

  if ( !IsIdentifier() )
    throw InvalidSyntaxException("Expected an identifier after 'prog'");

  get_token();

  if ( token.compare("blip") != 0 )
    throw InvalidSyntaxException("Expected 'blip' following Routine Declaration identifier");

  get_token();

  if ( token.compare("blorp") != 0 ) // Because the statement sequence is optional
  {
    if ( IsStatementSequence() )
    {
      if ( token.compare("blorp") != 0 )
        throw InvalidSyntaxException("Expected 'blorp' to end Routine Declaration");

        debug("\t\t\t\t\tBLORP!");

    }
    else
      throw InvalidSyntaxException("Expected a Statement Sequence after 'blip'");
  }

  // At this point the statement was accepted
} // End IsRoutineDeclaration




/**
 * Identifies a statement sequence
 */
bool IsStatementSequence ()
{
  debug("Entered IsStatementSequence");
  bool result = false;

  bool inLoop = true;
  do
  {
    if ( IsStatement() )
    {
      result = true;

      debug("statement repeition reading");
      get_token();
    }
    else
      inLoop = false;

  } while ( inLoop );

  return result;
} // End IsStatementSequence


/**
 * Tells if it is a statement
 */
bool IsStatement ()
{
  debug("Entered IsStatement");

  if ( IsAssignment() )
  {
    debug("Was part of statement");
    if ( token.compare("!") != 0 )
      throw InvalidSyntaxException("Expecting a '!' to follow a statement");

    debug("Ended statement");
    return true;

  }
  else if ( IsIfStatement() )
  {
    if ( token.compare("endif") != 0 )
      throw InvalidSyntaxException("Was expecting an 'endif' statement.");

    return true;
  }
  else
  {
    if ( IsRotateStatement() || IsLoopStatement() || IsForwardStatement() )
      return true;

  }

  debug("Not a statement");
  return false;
} // End IsStatementSequence


/**
 * Checks for a forward statement
 */
bool IsRotateStatement ()
{
  if ( token.compare("rotate") == 0 )
  {
    // Miners Dig Deeper!
    get_token();

    if ( token.compare("(") == 0 )
    {
      get_token();

      if ( IsExpression() )
      {
        get_token();

        if ( token.compare("!") == 0 )
          return true;

        else
          throw InvalidSyntaxException("Expecting '!' after rotate statement");
      }
      else
        throw InvalidSyntaxException("Expecting expression in rotate statement");
    }
    else
      throw InvalidSyntaxException("Expecting '(' in rotate expression");
  }

  return false;
} // End IsRotateStatement


/**
 * Checks for a forward statement
 */
bool IsForwardStatement ()
{
  if ( token.compare("forward") == 0 )
  {
    // Miners Dig Deeper!
    get_token();

    if ( token.compare("(") == 0 )
    {
      get_token();

      if ( IsExpression() )
      {
        get_token();

        if ( token.compare("!") == 0 )
          return true;

        else
          throw InvalidSyntaxException("Expecting '!' after forward statement");
      }
      else
        throw InvalidSyntaxException("Expecting expression in forward statement");
    }
    else
      throw InvalidSyntaxException("Expecting '(' in forward expression");
  }

  return false;
} // End IsForwardStatement


/**
 * Determines if a loop statement
 */
bool IsLoopStatement ()
{
  if ( token.compare("while") == 0 )
  {
      // Go deeper!
      get_token();

      if ( token.compare("(") == 0 )
      {
        get_token();

        if ( IsExpression() )
        {
          get_token();

          if ( IsStatementSequence() )
          {
            if ( token.compare("endw") == 0 )
              return true;

            throw InvalidSyntaxException("Expecint 'endw' after while statement sequence");
          }
          throw InvalidSyntaxException("Expecting Statement Sequence in while");
        }
        else
          throw InvalidSyntaxException("Expecting Statement in while");
      }
      else
        throw InvalidSyntaxException("Expecting '(' after 'while'");
  }

  return false;
} // End IsLoopStatement


/**
 * Determines if an if statement
 */
bool IsIfStatement ()
{
  if ( token.compare("if") == 0)
  {
      // Go deeper
      get_token();

      if ( token.compare("(") == 0 )
      {
        get_token();

        if ( IsExpression() )
        {
          get_token();

          if ( IsStatementSequence() )
          {
            if ( token.compare("else") == 0 )
            {
              get_token();

              if ( !IsStatementSequence() )
                throw InvalidSyntaxException("Expecting Statement Sequence in Else statement");
            }

            if ( token.compare("endif") == 0 )
              return true;
            else
              throw InvalidSyntaxException("Expecting 'endif' following if statement");
          }
          else
              throw InvalidSyntaxException("Was expecting a statement sequence in if statement");

        }
        else
          throw InvalidSyntaxException("Expected an Expression following '(' on if statement");
      }
      else
        throw InvalidSyntaxException("Expected a '(' after 'if'");
  }

  return false;
} // End IsIfStatement


/**
 * Tells if something is an assignment
 */
bool IsAssignment ()
{
  debug("Entered IsAssignment");

  if ( IsIdentifier() )
  {
    get_token();

    if ( token.compare("is") == 0 )
    {
      get_token();

      if ( IsExpression() )
      {
        debug("Assignment has an expression on the end, returning true");
        return true;
      }
      else
        throw InvalidSyntaxException("Expected an Expression in assignment following 'is'"); // Invalid syntax

    }
    else
      throw InvalidSyntaxException("Expecting 'is' after identifier in assignment statement.");

  }

  debug("Leaving IsAssignment with: false");
  return false; // Not an assignment
} // End IsAssignment




/**
 * Recognizes an expression
 */
bool IsExpression ()
{
  debug("Entered IsExpression");

  if ( IsSimpleExpression() )
  {
    if ( IsRelation() )
    {
      get_token();

      bool result = IsSimpleExpression();

      debug("Left Expression with:", result);
      return result;
    }

    debug("Left expression without a relation: true");

    return true;
  }

  debug("Left expression with: false");

  return false;
} // End IsExpression


/**
 * Checks for a simple expression
 *
 * Term { AddOperator Term }
 */
bool IsSimpleExpression ()
{
  debug("Entered IsSimpleExpression");
  if ( IsTerm() )
  {
    bool inLoop = true;

    do
    {
      if ( IsAddOperator() )
      {
        debug("Simple Expression had an Add Operator");
        get_token();

        if ( !IsTerm() )
          throw InvalidSyntaxException("Was expecting a term in expression.");
      }
      else
        inLoop = false;

    } while ( inLoop );

    debug("Leaving IsSimpleExpression with: true");
    return true;
  }

  debug("Leaving IsSimpleExpression with: false");
  return false;
} // End IsSimpleExpression



/**
 * checks if something is a term
 *
 * Factor { MultiOperator Factor }
 */
bool IsTerm ()
{
  debug("Entered IsTerm");

  if ( IsFactor() )
  {
    get_token();

    bool inLoop = true;

    do
    {
      if ( IsMultOperator() )
      {
        debug("Found a multioperator");
        get_token();

        if ( !IsFactor() )
          throw InvalidSyntaxException("Was expecting a factor in term");

        get_token(); // ????????????????? WHY?
      }
      else
        inLoop = false;
    } while ( inLoop );

    debug("Leaving IsTerm with: true");
    return true;
  }

  debug("Leaving IsTerm with: false");
  return false;
} // End IsTerm


/**
 * Checks for a factor
 */
bool IsFactor ()
{
  debug("Entered IsFactor");

  if ( IsInteger() || IsDecimal() || IsIdentifier() )
  {
    return true;
  }
  else
  {
    if ( token.compare("(") == 0 )
    {
      // Expression in parenthesis
      get_token();

      if ( !IsExpression() )
        throw InvalidSyntaxException("Expected Expression after '('");

      get_token();

      if ( token.compare(")") == 0 )
        return true;
      else
        throw InvalidSyntaxException("Expected ')' following Expression");
    }
    else
    {
      // Negated factor
      if ( token.compare("~") == 0 )
      {
        get_token();

        bool result = IsFactor();
        debug("Leaving IsFactor with: " + result);
        return result;
      }
    }
  }

  debug("Leaving IsFactor with: false");
  return false;
} // End IsFactor


/**
 * Determines if a string is an identifier
 *
 * regex: [A-Za-z]([A-Za-z]|[0-9]|_)*
 *
 * S -> [A-Za-z]B
 * B -> [0-9]B | [A-Za-z]B | '_'B
 */
bool IsIdentifier ()
{
  debug("Entered IsIdentifier");

  if ( IsKeyword() )
    return false; // Identifiers can't be keywords

  int state = 0;
  unsigned int pos = 0;

  char inp = token[pos];

  // Loop through all the characters in input
  while ( pos < token.length() )
  {
    switch ( state )
    {
        // Initial state, only allow letters
        case 0:
          if ( isalpha(inp) )
            state = 1;
          else
            return false; // Invalid

          break;

        // State 1, allow letters, numbers
        case 1:
          if ( !isalnum(inp) )
            return false; // Invalid

          break;
    }

    // Advance to the next character
    inp = token[++pos];
  }

  debug("Left IsIdentifier with:", (state == 1));
  return (state == 1); // Return true if in final state
} // End IsIdentifier



/**
 * State machine to check if input is a decimal number
 *
 * regex: (+|-)?[0-9]+\.[0-9]+
 *
 * S -> '+' | '-' | A'.'A
 * A -> [0-9]A
 */
bool IsDecimal ()
{
  debug("Entered IsDecimal");

  short state = 0;
  unsigned short pos = 0;

  char inp = token[pos];

  string before_decimal = "";

  // Loop through all of the characters
  while ( pos < token.length() )
  {

    switch ( state )
    {
      // Initial state, waiting for '.'
      case 0:
        if ( inp == '.' )
        {
          state = 1; // Decimal found, move onto after the decimal
        }
        else
        {
          before_decimal += inp; // Append to running string
        }
        break;

      // State 1, making sure stuff before the decimal is valid
      case 1:
        // Put everything back into the keyboard buffer
        cin.putback(' ');
        for ( short i = before_decimal.length() - 1; i >= 0; i-- )
          cin.putback(before_decimal[i]);

        get_token();

        if ( IsInteger() )
        {
          if ( isdigit(inp) )
            state = 2; // Move onto check what is after the decimal
          else
            return false; // Not valid
        }
        else
          return false; // Not valid

        break;

      // State 2 (final state), continue checking after decimal
      case 2:
        if ( !isdigit(inp) )
          return false;

        break;
    }

    // Advance to the next character
    inp = token[++pos];
  }

  return (state == 2); // Return true if in the final state
} // End IsDecimal


/**
 * State machine to determine if it is an integer
 *
 * regex: (+|-)?[0-9]+
 *
 * S -> '+' | '-' | A
 * A -> [0-9]A
 */
bool IsInteger ()
{
  debug("Entered IsInteger");
  short state = 0;
  unsigned short pos = 0;

  char inp = token[pos];

  // Continue reading until a token separator
  while ( pos < token.length() )
  {
    switch ( state )
    {
      // Initial state
      case 0:
        if ( inp == '+' || inp == '-' )
          state = 1; // Wait for a digit
        else if ( isdigit(inp) )
          state = 2; // Final state
        else
          return false;

        break;

      // State 1: force the next input to be a digit
      case 1:
        if ( isdigit(inp) )
          state = 2; // Goto final state
        else
          return false; // Invalid

        break;

      // Final state
      case 2:
        if ( !isdigit(inp) )
          return false; // Invalid
        break;
    }

    // Advance to next character
    inp = token[++pos];
  }

  debug("Leaving IsInteger with:", (state == 2));
  return (state == 2); // True if in final state
} // End IsInteger



/**
 * Identifies a keyword
 */
bool IsKeyword ()
{
  debug("Entered IsKeyword");
  string keywords[] = { "!", "~", "forward", "rotate", "if", "endif", "else", "while", "endw", "prog", "blip", "blorp", "is" };

  bool result = (IsRelation() || IsAddOperator() || IsMultOperator() || IsInArray(token, keywords, 13));

  debug("Left IsKeyword with:", result);
  return result;
} // End IsKeyword


/**
 * Checks if it is a Relation
 * < | > | = | #
 */
bool IsRelation ()
{
  debug("Entered IsRelation");
  string operators[] = { ">", "<", "=", "#" };

  bool result = IsInArray(token, operators, 4);
  debug("Left IsRelation with:", result);
  return result;
} // End IsRelation


/**
 * Checks if it is an Add Operator
 * + | - | "or"
 */
bool IsAddOperator ()
{
  debug("Entered IsAddOperator");
  string operators[] = { "+", "-", "or" };

  bool result = IsInArray(token, operators, 3);
  debug("Left IsAddOperator with:", result);

  return result;
} // End IsAddOperator


/**
 * Checks if it is a Mult Operator
 * / | * | "and"
 */
bool IsMultOperator ()
{
  debug("Entered IsMultioperator");
  string operators[] = { "/", "*", "and" };

  bool result = IsInArray(token, operators, 3);

  debug("Left IsMultioperator with:", result);
  return result;
} // End IsMultOperator





/**
 * Confirms a token exists
 */
bool token_exist ()
{
  return (cin.peek() != EOF);
}


/**
 * Consumes a token
 */
void get_token ()
{
  // Return false if there are no more characters in the input
  if ( !token_exist() )
    throw InvalidSyntaxException();

  // Get the next token from the stream
  cin >> token;

  debug("Got " + token);
}

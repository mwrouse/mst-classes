/*
	Program......: Assignment 1
	File.........: assignment1.cpp
	Student......: Michael Rouse
	Student ID...: 
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-09-22
	Description..: My First Lexical Analyzer
*/
#include <iostream>
#include <string>
#include <ctype.h>
#include "mylexer.h"


using namespace std;






/**
 * Main Function
 */
int main ()
{
  int lines_to_read = 0; // The number of lines to read from the input file
  string input; // The input read to check against the automata

  // Get the number of lines to read from input
  cin >> lines_to_read;
  cout << lines_to_read << endl; // Echo the number of lines to read

  // Loop while there are still lines to read
  for ( int i = 1; i <= lines_to_read; i++ )
  {
      cin >> input; // Read the input

      // Run through the state machines
      int result = recognize(input);

      // Output result
      cout << i << ": " << types[result] << endl;
  }

  return 0;
}




/**
 * Uses all of the state machines to determine what
 * type of token the input is.
 */
int recognize ( string input )
{
  // Compare input to each state machine
  if ( is_keyword(input) )
    return TOKEN_KEYWORD;

  if ( is_phone_number(input) )
    return TOKEN_PHONE;

  if ( is_hexadecimal(input) )
    return TOKEN_HEXADECIMAL;

  if ( is_integer(input) )
    return TOKEN_INTEGER;

  if ( is_decimal(input) )
    return TOKEN_DECIMAL;

  if ( is_scientific(input) )
    return TOKEN_SCIENTIFIC;

  if ( is_identifier(input) )
    return TOKEN_IDENTIFIER;

  // Unknown/Invalid token
  return TOKEN_INVALID;
} // End recognize




/**
 * Checks if input is a keyword
 *
 * regex: while|else|end|print
 *
 * S -> "while" | "else" | "end" | "print"
 */
bool is_keyword ( string input )
{
  string keywords[] = { "while", "else", "end", "print" };
  short number_of_keywords = 4;

  // Compare input to every keyword
  for ( short i = 0; i < number_of_keywords; i++ )
  {
      if ( input.compare(keywords[i]) == 0 )
        return true; // Match found, it is a keyword
  }

  return false;
} // End is_keyword




/**
 * The state machine to check if input is a phone number
 *
 * regex: \([0-9]{3}\)[0-9]{3}-[0-9]{4}|[0-9]{3}-[0-9]{3}-[0-9]{4}|[0-9]{3}\.[0-9]{3}\.[0-9]{4}
 *
 * S -> (A)A'-'B | A'.'A'.'B | A'-'A'-'B
 * A -> [0-9][0-9][0-9]
 * B -> A[0-9]
 */
bool is_phone_number ( string input )
{
  if ( input.length() != 12 && input.length() != 13 ) return false; // Invalid length

  int state = 0;
  unsigned int pos = 0;

  char inp = input[pos];

  int stack = 0; // Stack for counting the number of digits

  // Loop through all the characters
  while ( pos < input.length() )
  {
    // Reject if current character is invalid
    if ( !isdigit(inp) && inp != '(' && inp != ')' && inp != '.' && inp != '-' ) return false;

    switch ( state )
    {
        // Initial state
        case 0:
          if ( isdigit(inp) )
          {
            stack++;
          }
          // Check if parenthesis
          else if ( inp == '(' )
          {
            if ( stack == 0 )
              state = 1;
            else
              return false; // Not a valid phone number
          }
          // Check if period
          else if ( inp == '.' )
          {
            if ( stack == 3 )
              state = 3;
            else
              return false; // Not a valid phone number
          }
          // Check if dash
          else if ( inp == '-' )
          {
            if ( stack == 3 )
              state = 2;
            else
              return false; // Not a valid phone number
          }
          break;

        // State to monitor for parenthesis area code
        case 1:
          if ( isdigit(inp) )
            stack++;
          else
            // Check if ending parenthis was found
            if ( stack == 3 && inp == ')' )
              state = 2;
            else
              return false; // Not a phone number

          break;

      // State for finding first section of dashed separations after area code
      case 2:
        if ( isdigit(inp) )
          stack--; // Now, go backwards through the stack
        else
        {
          // Check if next separator was found
          if ( stack == 0 && inp == '-' )
            state = 4;
          else
            return false; // Not a valid phone number
        }

        break;

      // State for finding section after area code followed by a '.' separator
      case 3:
        if ( isdigit(inp) )
          stack--;
        else
          if ( stack == 0 && inp == '.' )
            state = 4; // Move to final state
          else
            return false; // Not a valid phone number

        break;

      // State for finding last four digits
      case 4:
        if ( isdigit(inp) )
          stack++;
        else
          return false; // Not a vlid phone number

        break;
    }


    // Advance to the next character in the input
    inp = input[++pos];
  }

  // Return true if ended in state 4 with 4 on the stack
  return ( state == 4 && stack == 4 );
} // End is_phone_number




/**
 * Checks if it is a Hexadecimal number
 *
 * regex: ([A-F] | [0-9])+'H'
 *
 * S -> A'H'
 * A -> [0-9]A | [A-F]A
 */
bool is_hexadecimal ( string input )
{
  unsigned int pos = 0;

  char inp = input[pos];

  // Loop through all characters in the string (except the last character)
  while ( pos < input.length() - 1 )
  {
      // Only allow valid Hexadecimal characters
      if ( !isdigit(inp) && (inp < 'A' || inp > 'F') ) return false;

      // Advance to next character
      inp = input[++pos];
  }

  // Check if the last character is a 'H'
  if ( inp == 'H' ) return true;

  return false;
} // End is_hexadecimal




/**
 * State machine to determine if it is an integer
 *
 * regex: (+|-)?[0-9]+
 *
 * S -> '+' | '-' | A
 * A -> [0-9]A
 */
bool is_integer ( string input )
{
  int state = 0;
  unsigned int pos = 0;

  char inp = input[pos];

  // Loop through all characters
  while ( pos < input.length() )
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
    inp = input[++pos];
  }

  return (state == 2); // True if in final state
} // End is_integer




/**
 * State machine to check if input is a decimal number
 *
 * regex: (+|-)?[0-9]+\.[0-9]+
 *
 * S -> '+' | '-' | A'.'A
 * A -> [0-9]A
 */
bool is_decimal ( string input )
{
  int state = 0;
  unsigned int pos = 0;

  char inp = input[pos];

  string before_decimal = "";

  // Loop through all of the characters
  while ( pos < input.length() )
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
        if ( is_integer(before_decimal) )
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
        if ( !isdigit(inp) ) return false;

        break;
    }

    // Advance to the next character
    inp = input[++pos];
  }

  return (state == 2); // Return true if in the final state
} // End is_decimal




/**
 * State machine to determine if it is scientific number or not
 *
 * regex: (\+|-)?[0-9]+\.[0-9]+E(\+|-)?0*[1-9][0-9]*
 *
 * S -> '+' | '-' | A'E'B
 * A -> [0-9]A
 * B -> '0'B | [1-9]B
 *
 */
bool is_scientific ( string input )
{
  int state = 0;
  unsigned int pos = 0;

  char inp = input[pos];

  string before_e = "";

  // Loop through all characters in the string
  while ( pos < input.length() )
  {
    switch ( state )
    {
        // Initial state, waiting to find 'e'
        case 0:
          if ( inp == 'E' )
          {
            state = 1; // Advance to next sate
          }
          else
          {
            before_e += inp; // Append to running string
          }
          break;

        // First state, valid before the e, and the first character after the e
        case 1:
          if ( is_decimal(before_e) )
          {
            if ( inp == '+' || inp == '-' || inp == '0' )
              state = 2; // Wait for a digit that is not zero to be entered
            else if ( isdigit(inp) )
              state = 3; // Goto final state
            else
              return false; // Invalid
          }
          else
            return false; // Not valid

          break;

        // Second state, wait for a number 1-9 to be entered
        case 2:
          if ( isdigit(inp) )
          {
            if ( inp != '0' )
              state = 3; // Goto final state
          }
          else
            return false; // Invalid

          break;

        // Final state
        case 3:
          if ( !isdigit(inp) ) return false; // Not valid

          break;
    }

    // Advance to the next character
    inp = input[++pos];
  }

  return (state == 3); // Return true if in final state
} // End is_scientific




/**
 * Determines if a string is an identifier
 *
 * regex: [A-Za-z]([A-Za-z]|[0-9]|_)*
 *
 * S -> [A-Za-z]B
 * B -> [0-9]B | [A-Za-z]B | '_'B
 */
bool is_identifier ( string input )
{
  int state = 0;
  unsigned int pos = 0;

  char inp = input[pos];

  // Loop through all the characters in input
  while ( pos < input.length() )
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

        // State 1, allow letters, numbers, and underscores
        case 1:
          if ( !isalnum(inp) && inp != '_' )
            return false; // Invalid

          break;
    }

    // Advance to the next character
    inp = input[++pos];
  }

  return (state == 1); // Return true if in final state
} // End is_identifier

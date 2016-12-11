/*
	Program......: Assignment 1
	File.........: assignment1.h
	Student......: Michael Rouse
	Student ID...: 12442296
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-09-22
	Description..: My First Lexical Analyzer
*/
#ifndef ASSIGNMENT1_H
#define ASSIGNMENT1_H

#include <iostream>
#include <string.h>

using namespace std;

/**
 * Types of Tokens
 */
#define TOKEN_INTEGER     1
#define TOKEN_DECIMAL     2
#define TOKEN_SCIENTIFIC  3
#define TOKEN_HEXADECIMAL 4
#define TOKEN_PHONE       5
#define TOKEN_KEYWORD     6
#define TOKEN_IDENTIFIER  7

#define TOKEN_INVALID 0

string types[] = { "INVALID!", "Integer.", "Decimal.", "Scientific.", "Hexadecimal.", "Phone.", "Keyword.", "Identifier." };


/**
 * Functions that implement a state machine
 */
int recognize ( string input );

bool is_phone_number ( string input );
bool is_keyword ( string input );
bool is_hexadecimal ( string input );
bool is_integer ( string input );
bool is_decimal ( string input );
bool is_scientific ( string input );
bool is_identifier ( string input );




#endif

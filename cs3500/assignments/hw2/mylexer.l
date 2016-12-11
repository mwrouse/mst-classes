/*
	Program......: Assignment 2
	File.........: mylexer.l
	Student......: Michael Rouse
	Student ID...: 
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-10-01
	Description..: Lexical Analyzer using flex
*/
%{
	#include <iostream>
	#include <string>
	#include <iomanip>
	
	#define	INT_CONST	"INTCONST"
	#define	DEC_CONST	"DECCONST"
	#define HEX_CONST	"HEXCONST"
	#define BIN_CONST	"BINCONST"
	#define	SCI_CONST	"SCI_CONST"
	#define	PH_CONST	"PHCONST"
	#define KEYWORD		"KEYWORD"
	#define STR_CONST	"STRCONST"
	#define OPERATOR	"OPERATOR"
	#define IDENTIFIER	"IDENT"
	#define UNKNOWN		"?"

	using namespace std;

	void output (string lexan_type);


	int line_count = 1; // Number of lines counted
	int token_count = 0; // Number of tokens counted

%}

%option noyywrap

NONZERO	  [1-9]
DIGIT     [0-9]

LOWERCASE [a-z]
UPPERCASE [A-Z]

HEX       ({DIGIT}|[A-F])
BINARY    [0-1]

LETTER    ({LOWERCASE}|{UPPERCASE})
ALPHANUM  ({LETTER}|{DIGIT})

SIGN	   ("+"|"-")

%% /* ---- Regular Expressions ---- */


[ \t]               ; /* Ignore spaces */
(\n|\r|\r\n)        { line_count++; } /* Increase line count */

"%"+(.*)?\n         { line_count++; } /* Ignore comments */

{SIGN}?{DIGIT}+              { output(INT_CONST); } /* Integer */
{SIGN}?{DIGIT}+"."{DIGIT}+   { output(DEC_CONST); } /* Decimal */

{SIGN}?{DIGIT}+"."{DIGIT}+"E"{SIGN}?"0"*{NONZERO}{DIGIT}*    { output(SCI_CONST); } /* Scientific Number */

{HEX}+"H"       { output(HEX_CONST); } /* Hexadecimal Number */
{BINARY}+"B"    { output(BIN_CONST); } /* Binary Number */

{DIGIT}{DIGIT}{DIGIT}"."{DIGIT}{DIGIT}{DIGIT}"."{DIGIT}{DIGIT}{DIGIT}{DIGIT}      { output(PH_CONST); } /* Phone Number 1 */
"("{DIGIT}{DIGIT}{DIGIT}")"{DIGIT}{DIGIT}{DIGIT}"-"{DIGIT}{DIGIT}{DIGIT}{DIGIT}   { output(PH_CONST); } /* Phone Number 2 */
{DIGIT}{DIGIT}{DIGIT}"-"{DIGIT}{DIGIT}{DIGIT}"-"{DIGIT}{DIGIT}{DIGIT}{DIGIT}      { output(PH_CONST); } /* Phone Number 3 */

("if"|"else"|"func"|"let"|"print"|"while")    { output(KEYWORD); } /* Keyword */


"\""({ALPHANUM}|[ \t])*"\""     { output(STR_CONST); } /* String Constant */

("+"|"-"|"*"|"/"|"<"|">"|"&")   { output(OPERATOR); } /* Operators */


{LETTER}{ALPHANUM}*	{ output(IDENTIFIER); } /* Identifier */


.       { output(UNKNOWN); } /* Unknown */

%%
/* ---- Coda ---- */


int main ()
{
	yylex();
	cout << line_count << " lines processed." << endl;

	return 0;
}



/**
 * This function is used to easily output results
 */
void output (string lexan_type)
{
	cout << "#" << token_count << ": TOKEN: " << setw(11) << left << lexan_type <<
		"LEXEME: " << string(yytext) << endl;

	token_count++;
}

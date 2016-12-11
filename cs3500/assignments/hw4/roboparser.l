/*
	Program......: Assignment 4
	File.........: roboparser.l
	Student......: Michael Rouse
	Student ID...: 12442296
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-12-09
	Description..: Roboparser - Flex part
*/
%{ 
	#include <iostream>
	#include <string> 
	#include <iomanip>
	#include "roboparser.tab.h"
	
	using namespace std; 
	
	#define YY_DECL extern "C" int yylex()
	
	/**
	 * Function.....: output 
	 * Parameters...: string token_type 
	 * Description..: Outputs the token type
	 */
	void output ( int token_type ); 
	
	
	int line_count = 1;
%}

%option noyywrap


NONZERO		[1-9]
DIGIT		[0-9]

LOWERCASE	[a-z]
UPPERCASE	[A-Z]

LETTER		({LOWERCASE}|{UPPERCASE})
ALPHANUM	({LETTER}|{DIGIT})

SIGN		("+"|"-")

RELATION	("<"|">"|"="|"#")

ADDOPERATOR	("+"|"-"|"or")

MULOPERATOR	("*"|"/"|"and")


%% /* ---- Regular Expresions ---- */

[ \t]		;
(\n|\r|\r\n) { line_count++; };



"is"		{ output( K_IS ); 		return K_IS; 		} /* Keywords */
"~"			{ output( K_NEG ); 		return K_NEG; 		}
"("			{ output( K_LPAREN ); 	return K_LPAREN;	}
")"			{ output( K_RPAREN ); 	return K_RPAREN;	}
"!"			{ output( K_BANG ); 	return K_BANG; 		}
"forward"	{ output( K_FORWARD ); 	return K_FORWARD; 	}
"rotate"	{ output( K_ROTATE ); 	return K_ROTATE;	}
"if"		{ output( K_IF ); 		return K_IF; 		}
"endif"		{ output( K_ENDIF ); 	return K_ENDIF; 	}
"else"		{ output( K_ELSE ); 	return K_ELSE; 		}
"while"		{ output( K_WHILE ); 	return K_WHILE;		}
"endw"		{ output( K_ENDW ); 	return K_ENDW; 		}
"prog"		{ output( K_PROG ); 	return K_PROG; 		}
"blip"		{ output( K_BLIP ); 	return K_BLIP; 		}
"blorp"		{ output( K_BLORP ); 	return K_BLORP; 	}



{SIGN}?{DIGIT}+					{ output( T_INTEGER );	return T_INTEGER;		} /* Integers */
{SIGN}?{DIGIT}+"."{DIGIT}+		{ output( T_DECIMAL ); 	return T_DECIMAL; 		} /* Decimals */

{LETTER}+{ALPHANUM}*			{ output( T_IDENT ); 	return T_IDENT; 		} /* Identifiers */

{RELATION}						{ output( T_RELATION ); return T_RELATION; 		} /* Relation */

{ADDOPERATOR}					{ output( T_ADDOPERATOR ); return T_ADDOPERATOR;	} /* Add level operators */
{MULOPERATOR}					{ output( T_MULOPERATOR ); return T_MULOPERATOR; 	} /* Multiplication level operators */




.	{ } /* Unknown input */


%% /* ---- Code ---- */

/**
 * Function.....: output 
 * Parameters...: string token_type 
 * Description..: Outputs the token type
 */
void output ( int token_type ) 
{
	string token_name = "";
	
	switch (token_type) { 
		case T_INTEGER: 	token_name = "T_INTEGER";		break;
		case T_DECIMAL: 	token_name = "T_DECIMAL"; 		break;
		case T_IDENT: 		token_name = "T_IDENT";			break;
		case T_RELATION:	token_name = "T_RELATION";		break;
		case T_ADDOPERATOR:	token_name = "T_ADDOPERATOR";	break;
		case T_MULOPERATOR:	token_name = "T_MULOPERATOR";	break;
		
		case K_IS: 		token_name = "K_IS";		break;
		case K_NEG:		token_name = "K_NEG"; 		break;
		case K_LPAREN:	token_name = "K_LPAREN"; 	break;
		case K_RPAREN:	token_name = "K_RPAREN"; 	break;
		case K_BANG:	token_name = "K_BANG"; 		break;
		case K_FORWARD:	token_name = "K_FORWARD"; 	break;
		case K_ROTATE:	token_name = "K_ROTATE"; 	break;
		case K_IF:		token_name = "K_IF"; 		break;
		case K_ENDIF:	token_name = "K_ENDIF"; 	break;
		case K_ELSE:	token_name = "K_ELSE"; 		break;
		case K_WHILE:	token_name = "K_WHILE"; 	break;
		case K_ENDW:	token_name = "K_ENDW"; 		break;
		case K_PROG:	token_name = "K_PROG"; 		break;
		case K_BLIP:	token_name = "K_BLIP"; 		break;
		case K_BLORP:	token_name = "K_BLORP"; 	break;
		
		default: token_name = "UNKNOWN"; 
	}
	
	cout << "TOKEN: " << setw(14) << left << token_name << "LEXEME: " << string(yytext) << endl;

}

/*
	Program......: Assignment 4
	File.........: roboparser.y
	Student......: Michael Rouse
	Student ID...: 12442296
	Class........: Comp Sci 3500
	Instructor...: Morales
	Date.........: 2016-12-09
	Description..: Roboparser - Bison part
*/
%{ 
	#include <iostream>
	#include <string>
	
	using namespace std;
	
	extern "C" int yylex();
	extern "C" int yyparse();
	extern "C" FILE *yyin;
	
	extern "C" int line_count;
	extern "C" char *yytext;
	
	// Handles errors
	void yyerror ( const char *str );
	
	void output ( string head, string body );
	
%}


%token T_INTEGER		
%token T_DECIMAL		
%token T_IDENT			
%token T_RELATION		
%token T_ADDOPERATOR	
%token T_MULOPERATOR	
%token K_IS			
%token K_NEG			
%token K_LPAREN		
%token K_RPAREN		
%token K_BANG			
%token K_FORWARD		
%token K_ROTATE		
%token K_IF			
%token K_ENDIF			
%token K_ELSE			
%token K_WHILE			
%token K_ENDW			
%token K_PROG			
%token K_BLIP			
%token K_BLORP			

%token UNKNOWN	

%start RoutineSequence



%% /* Grammer */


RoutineSequence: 
	RoutineDeclaration RoutineSequence 	{ output( "RoutineSequence", "RoutineDeclaration RoutineSequence" ); }
	|	{ output( "RoutineSequence", "empty" ); }
	;

RoutineDeclaration: 
	K_PROG T_IDENT K_BLIP StatementSequence K_BLORP		{ output( "RoutineDeclaration", "prog identifier blip StatementSequence blorp" ); }
	;

StatementSequence: 
	Statement StatementSequence 	{ output( "StatementSequence", "Statement StatementSequence" ); }
	| Statement 					{ output( "StatementSequence", "Statement" ); }
	;


Expression: 
	SimpleExpression								{ output( "Expression", "SimpleExpression" ); }
	| SimpleExpression T_RELATION SimpleExpression 	{ output( "Expression", "SimpleExpression Relation SimpleExpression" ); }
	;
	
SimpleExpression:
	Term 									{ output( "SimpleExpression", "Term" ); }
	| Term T_ADDOPERATOR SimpleExpression 	{ output( "SimpleExpression", "Term AddOperator SimpleExpression" ); } 
	;

Term: 
	Factor 						{ output( "Term", "Factor" ); }
	| Factor T_MULOPERATOR Term { output( "Term", "Factor MulOperator Term" ); }
	;

	
Factor: 
	T_INTEGER						{ output( "Factor", "integer" ); }
	| T_DECIMAL						{ output( "Factor", "decimal" ); }
	| T_IDENT 						{ output( "Factor", "identifier" ); }
	| K_LPAREN Expression K_RPAREN 	{ output( "Factor", "( Expression )" ); }
	| K_NEG Factor 					{ output( "Factor", "~ Factor" ); }
	;
	
	
Assignment: 
	T_IDENT K_IS Expression K_BANG { output( "Assignment", "identifier is Expression !" );}
	;

FwdStatement: 
	K_FORWARD K_LPAREN Expression K_RPAREN K_BANG {output( "FwdStatement", "forward ( Expression ) !" ); }
	;
	
RotStatement:
	K_ROTATE K_LPAREN Expression K_RPAREN K_BANG { output( "RotStatement", "rotate ( Expression ) !" ); }
	;

IfStatement: 
	K_IF K_LPAREN Expression K_RPAREN StatementSequence K_ENDIF 							{ output( "IfStatement", "if ( Expression ) StatementSequence endif " ); }
	| K_IF K_LPAREN Expression K_RPAREN StatementSequence K_ELSE StatementSequence K_ENDIF	{ output( "IfStatement", "if ( Expression ) StatementSequence else StatementSequence endif" ); }
	;

LoopStatement: 
	K_WHILE K_LPAREN Expression K_RPAREN StatementSequence K_ENDW 	{ output( "LoopStatement", "while ( Expression ) StatementSequence endw" ); }
	;
	
Statement: 
	Assignment		{ output( "Statement", "Assignment" );}
	| IfStatement 	{ output( "Statement", "IfStatement" ); }
	| LoopStatement { output( "Statement", "LoopStatement" ); }
	| FwdStatement	{ output( "Statement", "FwdStatement" ); }
	| RotStatement	{ output( "Statement", "RotStatement" ); }
	| 				{ output( "Statement", "empty" ); }
	;
	




%% 


int main ( ) { 
	yyparse();
	
	cout << "CORRECT" << endl;
	
	return 0;
}


/**
 * Function.....: yyerror 
 * Description..: Handles parse errors 
 */
void yyerror ( const char *str ) {
	cout << "ERROR: In line " << line_count << " with token '" << string(yytext) << "'" << endl;
	cout << "INVALID!" << endl;
	

	exit(0);
}



void output ( string head, string body )
{
	cout << "RULE: " << head << " ::= " << body << endl;
}
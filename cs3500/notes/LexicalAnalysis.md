# Lexical Analysis
Lexical analysis is a step in a compiler that converts a string of characters (input) into a string of *tokens with a meaning.*

A program that performs lexical analysis is a *Lexer.*

## Definitions 
A *Lexeme* is a syntactical unit in a language   
A *Token* represents a lexeme and indicates a "category" for the purpose of parsing. 

**Example:** `int a = 9 * 9;`   

| Lexeme    | Token |
|-----------|-------|
| int       | TYPE  |
| a         | IDENTIFIER |
| =	    | ASSIGNMENT |
| 9         | INT LITERAL |
| *         | MULTIPLICATION |
| 9         | INT LITERAL |
| ;         | END STATEMENT |


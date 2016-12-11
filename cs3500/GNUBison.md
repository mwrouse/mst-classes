# GNU Bison 
GNU Bison is a parser generator similar to Flex. 

### Bison Spec File (filename.y) 
| Section | Contents | 
|---------|----------|
|Pre-amble| Commands/Directives | 
|separator|%%|
|Grammar| S: C C { action };|
||C: "a"C \| "b";|
||%%|
|Coda| C/C++ Code copied into output file |

``%start S`` in the Pre-amble tells bison that *S is the start symbol*

### Bison Functions 
| Function | Return Value | Description | 
|----------|:--------------:|-------------|
| ```yyparser()```| n/a | Calls parsing function (depends on yylex())|
| ```yyerror(const char*)``` |n/a|Called when parsing error occurs|
| ```yylex()``` | ```int``` | Stores tokens in global variable ```yytext```, returns int representing token type |

**Bison will not autogenerate yyerror(const char*) function**   
*Parameter of yyerror is the error message*

### Bison Special Variables 
| Variable | Type | Description | 
|----------|:----:|-------------|
| ```yytext```|```char[]```| Global variable for the lexeme/token |
|```yylval```||Global variable of the matched value (semantic value) |

## Using Bison 
In order to use bison you must: 
1. Declare token types in pre-amble 
2. Declare type(s) of yylval in pre-amble 
3. Use actions to give semantic value to non-terminals 
4. Add hints to resolve ambiguity (hacks) 
5. Define yylex() and yyerror()

### Declaring Tokens 
```%token TOKEN_TYPE``` declares a token type in Bison   

**Example:** 
```
%token INTEGER_LITERAL
%token DECIMAL_LITERAL
%token HEX_LITERAL 
```
declares three token types, INTEGER_LITERAL, DECIMAL_LITERAL, and HEX_LITERAL

Bison will automatically assign tokens an integer value 


### Bison Hacks 
``` 
%left TOKEN 
```
Tells Bison to prefer left-derivation for a TOKEN 

### Semantic Value 
To set semantic value to a token use    
```$$ = value;``` in an action 

To get the semantic value of the last matched token(s), use:    
```$1 ... $n``` in an action  
 
### Compiling Bison 
To compile Bison use the following command:    
```bison -d filename.y```

## Using Bison with Flex 
Flex and Bison can work together to form a parser.   
Flex defines yylex() function for Bison, and each action in Flex will return the type of token matched. 

### Bison/Flex Make File 
When using Bison and Flex together, use a make file with the following structure:
1. Compiled Bison 
2. Compile Flex 
3. Compile Everything

To view an example of this look at [homework 4](https://github.com/mwrouse/mst-classes/assignments/hw4)


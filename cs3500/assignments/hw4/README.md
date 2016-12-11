# Flex + Bison Parser 
Due: December 9, 2016 11:59:59pm   

Write a parser using `Flex` and `Bison` to recognize valid programs of the **Robolang-16.3** programming language. 


## Submission Guidelines 
Submit via `cssubmit`. You will submit two files that shall be called "roboparser.l" and "roboparser.y".    
Your files should include your name.  

Your program will be tested using the following chain of commands:    
```
bison -d roboparser.y    
flex roboparser.l    
g++ roboparser.tab.c lex.yy.c -o roboparser.ex      
roboparser.ex < inputFileName
```

## Flex Guidelines 
Your Flex lexical analyser should recognize the following tokens:    
`T_INTEGER` : non-empty sequences of digits optionally preceded with either a ‘+’ or ‘-’ sign.    
`T_DECIMAL` : numbers are Integers followed by a ‘.’, followed by a non-empty sequence of digits.    
`T_IDENT` are a sequences of digits or letters. The first character must be a letter, and an identifier cannot be a Keyword.     
`T_RELATION` : the terminal symbols <, >, =  and  #.    
`T_ADDOPERATOR` : the terminal symbols +, -,  and  or.    
`T_MULOPERATOR` : the terminal symbols *, /,  and  and.     

Keywords will each have their own token type. Keywords are the following strings: is, ~, (, ), !, forward, rotate, if, endif, else, while, endw, prog, blip, blorp; that flex should recognize as tokens `K_IS`, `K_NEG`, `K_LPAREN`, `K_RPAREN`, `K_BANG`, `K_FORWARD`, `K_ROTATE`, `K_IF`, `K_ENDIF`, `K_ELSE`, `K_WHILE`, `K_ENDW`, `K_PROG`, `K_BLIP` and `K_BLORP`.    
 
Whenever flex finds and return a token it should print a message of the form:    
`TOKEN: <TokenType>     LEXEME : <Lexeme>`    

**Reminder:** In Robolang tokens are always separated by white-spaces.

## Bison Guidelines 
Programs in the Robolang programming language conform to the following EBNF grammar where: `RoutineSequence`  is the start symbol.    

Terminal symbols are in bold.  Collections of terminal symbols are in italics.  Brackets,  ‘[‘ and ‘]’ , denote an optional section of a rule.  Braces,  ‘{‘ and ‘}’,  denote repetition of a rule section (possibly 0 times). 


`Expression` := `SimpleExpression` [ *`Relation` *`SimpleExpression` ]    
`SimpleExpression` := `Term` { *`AddOperator`* `Term` }    
`Term` := `Factor` { *`MulOperator`* `Factor` }    
`Factor` :=  *`integer`* | *`decimal`* | *`identifier`* | **`(`** `Expression` **`)`** | ~ `Factor`   

`Assignment` := *`identifier`* **`is`** `Expression` **`!`**    
`FwdStatement` := **`forward (`** `Expression` **`) !`**    
`RotStatement` = **`rotate (`**  `Expression` **`) !`**    
`IfStatement` := **`if (`** `Expression` **`)`** `StatementSequence` [ **`else`** `StatementSequence` ] **`endif`**    
`LoopStatement` = **`while (`**  `Expression` **`)`** `StatementSequence` **`endw`**    

`Statement` := [ `Assignment` | `IfStatement` | `LoopStatement` | `FwdStatement` | `RotStatement` ]    
`StatementSequence` = `Statement` { `Statement` }    

`RoutineDeclaration` := **`prog`** *`identifier`* **`blip`** [ `StatementSequence` ] **`blorp`**    

`RoutineSequence` := `RoutineDeclaration` { `RoutineDeclaration` }    

Bison does not supports EBNF, so you will have to transform the grammar to something acceptable by Bison, and that works together with the return types of Flex.

Whenever Bison is able to match a rule, output a message of the format:    
`RULE: <Head>  ::= <BODY> `    
As much as possible, try to match the format of the sample input output.


## Samples 
### Sample 1 
**Input:**    
```
prog main
blip
  x is 2 + 2 !
  forward ( x * 100 ) !
blorp
```

**Output:**   
```
TOKEN: K_PROG        LEXEME: prog
TOKEN: T_IDENT       LEXEME: main
TOKEN: K_BLIP        LEXEME: blip
TOKEN: T_IDENT       LEXEME: x
TOKEN: K_IS          LEXEME: is
TOKEN: T_INTEGER     LEXEME: 2
RULE: Factor ::= integer
TOKEN: T_ADDOPERATOR LEXEME: +
RULE: Term ::= Factor
TOKEN: T_INTEGER     LEXEME: 2
RULE: Factor ::= integer
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: SimpleExpression ::= Term AddOperator SimpleExpression
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: K_FORWARD     LEXEME: forward
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: x
RULE: Factor ::= identifier
TOKEN: T_MULOPERATOR LEXEME: *
TOKEN: T_INTEGER     LEXEME: 100
RULE: Factor ::= integer
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: Term ::= Factor MulOperator Term
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
TOKEN: K_BANG        LEXEME: !
RULE: FwdStatement ::= forward ( Expression ) !
RULE: Statement ::= FwdStatement
TOKEN: K_BLORP       LEXEME: blorp
RULE: StatementSequence ::= Statement
RULE: StatementSequence ::= Statement StatementSequence
RULE: RoutineDeclaration ::= prog identifier blip StatementSequence blorp
RULE: RoutineSequence ::= empty
RULE: RoutineSequence ::= RoutineDeclaration RoutineSequence
CORRECT

```

### Sample 2
**Input:**    
```
prog square
blip
  x is 90 !
  y is 100 !
  c is 1 !
  while ( c < 4 ) 
    forward ( y ) !
    rotate ( x ) !
    c is c + 1 !
  endw
blorp
```
**Output:**    
```
TOKEN: K_PROG        LEXEME: prog
TOKEN: T_IDENT       LEXEME: square
TOKEN: K_BLIP        LEXEME: blip
TOKEN: T_IDENT       LEXEME: x
TOKEN: K_IS          LEXEME: is
TOKEN: T_INTEGER     LEXEME: 90
RULE: Factor ::= integer
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: T_IDENT       LEXEME: y
TOKEN: K_IS          LEXEME: is
TOKEN: T_INTEGER     LEXEME: 100
RULE: Factor ::= integer
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: T_IDENT       LEXEME: c
TOKEN: K_IS          LEXEME: is
TOKEN: T_INTEGER     LEXEME: 1
RULE: Factor ::= integer
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: K_WHILE       LEXEME: while
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: c
RULE: Factor ::= identifier
TOKEN: T_RELATION    LEXEME: <
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
TOKEN: T_INTEGER     LEXEME: 4
RULE: Factor ::= integer
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression Relation SimpleExpression
TOKEN: K_FORWARD     LEXEME: forward
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: y
RULE: Factor ::= identifier
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
TOKEN: K_BANG        LEXEME: !
RULE: FwdStatement ::= forward ( Expression ) !
RULE: Statement ::= FwdStatement
TOKEN: K_ROTATE      LEXEME: rotate
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: x
RULE: Factor ::= identifier
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
TOKEN: K_BANG        LEXEME: !
RULE: RotStatement ::= rotate ( Expression ) !
RULE: Statement ::= RotStatement
TOKEN: T_IDENT       LEXEME: c
TOKEN: K_IS          LEXEME: is
TOKEN: T_IDENT       LEXEME: c
RULE: Factor ::= identifier
TOKEN: T_ADDOPERATOR LEXEME: +
RULE: Term ::= Factor
TOKEN: T_INTEGER     LEXEME: 1
RULE: Factor ::= integer
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: SimpleExpression ::= Term AddOperator SimpleExpression
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: K_ENDW        LEXEME: endw
RULE: StatementSequence ::= Statement
RULE: StatementSequence ::= Statement StatementSequence
RULE: StatementSequence ::= Statement StatementSequence
RULE: LoopStatement ::= while ( Expression ) StatementSequence endw
RULE: Statement ::= LoopStatement
TOKEN: K_BLORP       LEXEME: blorp
RULE: StatementSequence ::= Statement
RULE: StatementSequence ::= Statement StatementSequence
RULE: StatementSequence ::= Statement StatementSequence
RULE: StatementSequence ::= Statement StatementSequence
RULE: RoutineDeclaration ::= prog identifier blip StatementSequence blorp
RULE: RoutineSequence ::= empty
RULE: RoutineSequence ::= RoutineDeclaration RoutineSequence
CORRECT
```

### Sample 3 
**Input: **    
```
prog gcd
blip
  while ( ~ ( a = b ) )
    if ( a > b ) 
      a is a - b !
    else
      b is b - a !
    endif
  endw
blorp


prog dummy blip blorp 
```

**Output:**     
```
TOKEN: K_PROG        LEXEME: prog
TOKEN: T_IDENT       LEXEME: gcd
TOKEN: K_BLIP        LEXEME: blip
TOKEN: K_WHILE       LEXEME: while
TOKEN: K_LPAREN      LEXEME: (
TOKEN: K_NEG         LEXEME: ~
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: a
RULE: Factor ::= identifier
TOKEN: T_RELATION    LEXEME: =
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
TOKEN: T_IDENT       LEXEME: b
RULE: Factor ::= identifier
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression Relation SimpleExpression
RULE: Factor ::= ( Expression )
RULE: Factor ::= ~ Factor
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression
TOKEN: K_IF          LEXEME: if
TOKEN: K_LPAREN      LEXEME: (
TOKEN: T_IDENT       LEXEME: a
RULE: Factor ::= identifier
TOKEN: T_RELATION    LEXEME: >
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
TOKEN: T_IDENT       LEXEME: b
RULE: Factor ::= identifier
TOKEN: K_RPAREN      LEXEME: )
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: Expression ::= SimpleExpression Relation SimpleExpression
TOKEN: T_IDENT       LEXEME: a
TOKEN: K_IS          LEXEME: is
TOKEN: T_IDENT       LEXEME: a
RULE: Factor ::= identifier
TOKEN: T_ADDOPERATOR LEXEME: -
RULE: Term ::= Factor
TOKEN: T_IDENT       LEXEME: b
RULE: Factor ::= identifier
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: SimpleExpression ::= Term AddOperator SimpleExpression
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: K_ELSE        LEXEME: else
RULE: StatementSequence ::= Statement
TOKEN: T_IDENT       LEXEME: b
TOKEN: K_IS          LEXEME: is
TOKEN: T_IDENT       LEXEME: b
RULE: Factor ::= identifier
TOKEN: T_ADDOPERATOR LEXEME: -
RULE: Term ::= Factor
TOKEN: T_IDENT       LEXEME: a
RULE: Factor ::= identifier
TOKEN: K_BANG        LEXEME: !
RULE: Term ::= Factor
RULE: SimpleExpression ::= Term
RULE: SimpleExpression ::= Term AddOperator SimpleExpression
RULE: Expression ::= SimpleExpression
RULE: Assignment ::= identifier is Expression !
RULE: Statement ::= Assignment
TOKEN: K_ENDIF       LEXEME: endif
RULE: StatementSequence ::= Statement
RULE: IfStatement ::= if ( Expression ) StatementSequence else StatementSequence endif
RULE: Statement ::= IfStatement
TOKEN: K_ENDW        LEXEME: endw
RULE: StatementSequence ::= Statement
RULE: LoopStatement ::= while ( Expression ) StatementSequence endw
RULE: Statement ::= LoopStatement
TOKEN: K_BLORP       LEXEME: blorp
RULE: StatementSequence ::= Statement
RULE: RoutineDeclaration ::= prog identifier blip StatementSequence blorp
TOKEN: K_PROG        LEXEME: prog
TOKEN: T_IDENT       LEXEME: dummy
TOKEN: K_BLIP        LEXEME: blip
TOKEN: K_BLORP       LEXEME: blorp
RULE: Statement ::= empty
RULE: StatementSequence ::= Statement
RULE: RoutineDeclaration ::= prog identifier blip StatementSequence blorp
RULE: RoutineSequence ::= empty
RULE: RoutineSequence ::= RoutineDeclaration RoutineSequence
RULE: RoutineSequence ::= RoutineDeclaration RoutineSequence
CORRECT
```

### Sample 4 
**Input:**    
```cpp
void main ( ) {
  cout << "Hello World";
}
```

**Output:**    
```
TOKEN: T_IDENT       LEXEME: void
RULE: RoutineSequence ::= empty
ERROR: In line 1 with token 'void'
INVALID!
```



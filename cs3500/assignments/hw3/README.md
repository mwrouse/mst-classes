# Recursive Descent Parser 
Due: November 11, 2016 11:59:59pm   

Write a Recursive Descent Parser using the techniques used in class to recognize valid programs of the Robolang-16.3 Programming Language. 

## Submission Guidelines 
Submit via ‘cssubmit’. Your main file shall be called “roboparser” regardless of extension. (e.g. if you are programming in C++, your main file should be called “roboparser.cpp”. If you are programming in Java your main file should be called “roboparser.java” ).  Your main file should include your name.  Include any other necessary files in your submission. If you submit a makefile,  make should generate an executable called roboparser.ex.    

Your program will be tested with the command:    
        `roboparser.ex < inputFileName`

## Description 
Programs of the Robolang programming language are build from the following tokens: 

**`Integers`** are non-empty sequences of digits optionally preceded with either a '+' or ‘-' sign.   
**`Decimal`** numbers are Integers followed by a '.' followed by a non-empty sequence of digits.     
**`Keywords`** are the following strings: is, +, -, *, /, or, and, ~, (, ), <, >, = , #, !, forward, rotate, if, endif, else, while, endw, prog, blip, blorp.     
**`Identifiers`** are a sequences of digits or letters. The first character must be a letter, and an identifier cannot be a Keyword.     

*Tokens are **always** separated by white-spaces.*


### Grammar 
Programs in the Robolang programming language conform to the following EBNF grammar where:     
"RoutineSequence"  is the start symbol.     
Terminal symbols are in bold.     
Collections of terminal symbols are in italics    
Brackets,  ‘[‘ and ‘]’ , denote an optional section of a rule.      
Braces,  ‘{‘ and ‘}’,  denote repetition of a rule section (possibly 0 times).    

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


### Input 
Your parser should accept input from "standard input" and output to "standard output" 

### Output 
If the input program is valid, output "`CORRECT`," otherwise output "`INVALID!`."


## Sample 1 
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
CORRECT 
```

## Sample 2 
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
CORRECT 
```

## Sample 3 
**Input:**        
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
CORRECT 
```

## Sample 4 
**Input:**     
```
void main ( ) {
  cout << “Hello World”;
}
```

**Output:**        
```
INVALID!
```

## Sample 5 
**Input:**    
```
prog foo ( loop )
blip blip !
  x is blorp !
  forward ( rotate ) !
if
```

**Output:**   
```
INVALID! 
```

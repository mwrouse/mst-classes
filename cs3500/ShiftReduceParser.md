# Shift Reduce Parser
Shift Reduce Parsers are LR(1), **bottom-up** parsers that handle one symbol at a time.

#### Terminology 
*Shifting* is moving onto the next input symbol   
*Reducing* is converting a symbol to a non-terminal  
*Bottom-Up* is starting at non-terminals that turn to terminals and working way up to start symbol   
*LR Parser* means Left to Right and right most 


#### Example
**Grammar:**  
`E -> EAT | T`   
`T -> TBint | int`    
`A -> "+" | "-"`    
`B -> "*" | "/"`  


**Input:** 3 + 5 / 8


**Steps:**         

        T               |
        |               | - Reducing
        3 + 5 / 8       |
           
         T A            | Shift (moved to next symbol "+")
         | |
         3 + 5 / 8
             . 
             .
             . 
             E          <- Works to start symbol
         /   |    \
        E    A     T 
        |    |   / | \ 
        T    +  T  B  8
        |    .  |  |  .
        3    +  5  /  8 

### LR Parsers 
LR Parsers parse from left to right and use right-most derivation. 

* Only suitable on LR Grammars 
* Do not like ambiguity 


###Shift-Reduce Conflict 
The Shift-Reduce Conflict occurs when an LR parser encounters ambiguity, when it cannot decide whether to shift, or to reduce. 


**Example:**   
`S -> ab | Ab`  
`A -> a`  

**input:** ab   

Does the parser shift, or reduce first?


## Shift-Reduce Parser Tables
Shift-Reduce parsers generate tables that implement a *push-down automata*


The **Goto Table** is used to determine the next state after a reduction  
The **Action Table** is used to determine what to do based on an input 


#### Example 
`S -> CC`                 
`C -> aC`   
`C -> b`  

**input:** abb 

The parser first gives a number to each production rule:    
(1) S -> CC   
(2) C -> aC    
(3) C -> b   

**Goto Table**
*Columns in a Goto Table represent the non-terminals*    

|State |  S  |  C  |   
|:------:|:-----:|:-----:|
| 0 | 1 | 2 | 
| 1 | | | 
| 2 | | 5 | 
|3||8|
|4|||
|5|||
|6||9|
|7|||
|8|||
|9|||

**Action Table**
*Columns in an Action Table represent the terminals ($ is end of input)*    

|State| a | b|$|
|------|---|---|---|
|0|S3|S4||
|1|||acc|
|2|S6|S7||
|3|S3|S4||
|4|R3|R3||
|5|||R1|
|6|S6|S7||
|7|||R3|
|8|R2|R2||
|9|||R2|

*acc* - accept state   
*Sn* - Shift and goto state n   
*Rn* - Reduce by rule n     
*When reducing: pop from the stack the # of symbols of the body of the rule used to reduce*  
# Grammar 
Grammar is another solution to the **specification problem**

**Grammar** is a set of rules for transforming strings 

&nbsp; 

Given alphabet S (terminal symbols), non-terminal symbols (N), production rules (P), and a start symbol S (S ? N): 

`A -> x` where A ? N and x is a string of terminals and non terminals 

This is *context-free grammar.*

(A is called the *head*, x is the *body*)

**Example:** `S = {a, b}` `N = {S, P, Q}`

Production Rules: 

S -> aPQ 

P -> PQa 

Q -> bb 

P -> ab 

---
A *sentence* is a **string of terminals and non-terminals**

A *derivation* is a **repeated rule application**

A *language* is **any string of terminals that can be derived from a sentence**.

&nbsp; 

**Example:** S = {x, y, +, -} 

S -> SAS                                         

S -> x                                                               

S -> y

A -> +

A -> - 

---

### Parse Trees 
A Parse Tree is a representation of a derivation 

           S 
        /  |  \
       S   A   S   - Internal nodes (non-terminal)
      /|\  |   |
     S A S -   x   - Leaf nodes (terminal)
     | | |
     x + y

### Ambiguous Grammar 
Grammar is ambiguous when one string has more than one parse tree, or more than one right/left most derivation. 

## Backus-Naur Form (BNF)
BNF grammar was developed for *Algol-60* in the *1960s* to solve the **specification problem**

**Syntax:**

`::=` Production Rule 

`<X>`  X is a non-terminal 

`"x"`  x is a terminal symbol 


**Example:** previous grammar in BNF

`<S> ::= <S><A><S> | "x" | "y"`

`<A> ::= "+" | "-"`

### Extended Backus-Naur Form (EBNF) 
Adds the following: 

```[option]``` Matches 0 or 1 occurrences 

```{repetition}``` Matches 0+ occurrences 

```.``` Terminator 

**EBNF does not require < and > around non-terminals**
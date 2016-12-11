# Specification of Semantics 
Specification of Semantics is giving meaning to a language. 

There are three approaches to this: *Attribute Grammars*, *Axiomatic Semantics*, and *Denotational Semantics*.

## Attribute Grammars 
An *Attribute Grammar* adds type checking and scope to a languages grammar. 

**Let every symbol have a set of attributes, each attribute can have a value** 
     
Symbols: `{S, E, A, B}`   
Attributes: `{x, y}`   

          (S){,} <-- Attributes {x,y}
         /   \
    {,}(E)    (E){,}
        |     /   \
        . {,}(A)  (B){,}
              |    |
              .    .  

Rules for attributes can be:   
*Inherited* - value comes from children    
*Synthesized* - value comes from horizontally  


#### Example 
`E -> C1PC2`   
`C -> A | B | E`     
`A -> int`   
`B -> decimal`   
`P -> '+' | '-'`   

**Attribute Rules:**   
`E.type = int` if `C1.type = int` and `C2.type = int` else `E.type = float`    
`A.type = int`   
`B.type = float`     
`C.type` comes from if it is A, B, or E  

**input:** 3.14 + 23 - 5     

                       E (float,5)
             /         |       \
    (float,1)C         P        C(int,4)
             |         |        |
    (float,1)B         +        E (int,4)
             |                / | \   
            3.14      (int,2)C  P  C(int,3)      
                             |  |  |
                      (int,2)A  -  A (int,3)
                             |     |
                             23    5

The tree above has the following next to each non-terminal, it represents the attributes `(type, order of type discovery)`  


## Axiomatic Semantics 
Developed in 1969 by Charles Hoare 

*Axiomatic Semantics* adds **Predicate Logic**, creating *Hoare Logic*.    

*Adds rules to create a mathematical meaning to programs and reason about them*

#### Definitions 
A *state* (of computation) is a set of **`<variable, value>` pairs**    
A *computation* is a **sequence of states**   
An *assertion* is a **sentence in predicate logic about a state** (denotes a set of states [{x > 3} is all states where x > 3] )     

A *sentence* in Hoare logic has the following form:   
`{A} P {B}`   
where:   
`{A}` is the precondition, `A` is an assertion   
`P` is a program   
`{B}` is the post condition, `B` is an assertion    

*A sentence is evaluated to `True` or `False`*


### Axiom of Assignment 
The *Axiom of Assignment* states that a sentence in the form of:    
`{ Qx -> E }  x := E { Q }` is always `True`.

**Examples:**   
`{ 3 * 4 > 0 }  a := 3 * 4 { a > 0 }`  
`{ b < 22 } a := (b / 2) - 1 { a < 10 }`   
`{ (y * 37) > 3 } x := (y * 37) - 3 { x > 0 }`   


### Rule of Condition 
`{ B ^ P } S { Q } ^ { ¬B ^ P } T { Q }`  
concludes:   
`{ P } if B then S else T endif { Q }` 


### While Rule (important) 
` { P ^ B } S { P }`   
concludes:   
`{ P ^ B } while B then S endw { P ^ ¬B }`  

`P` is the *loop invariant*, it is the same before and after the loop. 



## Denotational Semantics 
*Denotational Semantics* is the most widely used version of semantic specification. 

Two things are needed:    
1. A collection of mathematical objects     
2. A function (`M`) for every rule      

#### Example 
`D -> 零 | 一 | 二 | 三 | 四 | 五 | 六 | 七 | 八 | 九`  (0-9 in Japanese)   
`N -> ND | λ`   

So far, the string `七一五` is valid, but it **has no meaning**.

**Mathematical object:** Z (set of all integers)   

**Functions:**   
`MD(零) = 0` , `MD(一) = 1`, `MD(二) = 2` ... `MD(九) = 9`      
`MN(ND) = MN(N) * 10 + MD(D)`, `MN(λ) = 0`

**Find the meaning of:** `七一五`    
                 
               N 
             /   \
            N     D
           /  \   |    
          N    D  五
         / \   | 
        N   D  一
        |   |
        λ   七

    MN(七一五) = MN(七一)*10  + MD(五) 
              = MN(七)*100 + MD(一)*10 + 5
              = 7*100  + 1*10 + 5 
              = 700 + 10 + 5 
              = 715

The string `七一五` now has a meaning of `715`
 
 ### Denotational Semantics State 
 Adding a state to denotational semantics allows for *more complex meanings* 

A *state* in denotational semantics is a set of `<variable, value>` pairs:   
` S = { <x1, v1>, <x2, v2>, ..., <xn, vn> }`   

We can then do: 
`VAL(S, xi) = vi`  

#### Example  
`E -> T | B`   
`T -> N | var`   
`B -> T1PT2`   
`P -> 💩 | 👽`      
`D -> 零 | 一 | 二 | 三 | 四 | 五 | 六 | 七 | 八 | 九`    
`N -> ND | λ`  

**Functions:**   
`MT(N, S) = MN(N)`, `MN(var, S) = VAL(S, var)`    
`MB(T1PT2, S) = MT(T1, S) MP(P) MT(T2,S)`   
`MP(💩) = /`, `MP(👽) = -`    
`ME(T, S) = MT(T, S)`, `ME(B, S) = MB(B, S)`    
where `S` is a state 

**Find meaning of:** `一四👽y` in the state `{<x, 0>, <y, 3>}`    
Let `S = {<x, 0>, <y, 3>}` (the state) 

                       B
               /       |       \
              T        P        T
              |        |        | 
              N        👽       y 
            /   \     
           N      D 
          /  \    | 
         N    D   四
         |    | 
         λ    一  

    MB(一四👽y, S)
    => MT(一四, S) 👽 MT(y, S) 
    => MN(一四) - VAL(y, S) 
    => 14 - 3 
    => 11
So, `一四👽y` in the state `{<x, 0>,<y, 3>}` means `11`  


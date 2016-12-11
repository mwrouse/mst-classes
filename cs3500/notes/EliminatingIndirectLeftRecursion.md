# Eliminating Indirect Left Recursion 
*d, ﬂ are strings of terminals & non-terminals*  

&nbsp;

#### Definition
Indirect Left Recursion takes the following form:     
`A -> Bx`    
`B -> Ay`   

## Elimination 
To eliminate indirect left recursion:    
1. Numbers rules as A1, A2, ... An    
2. For i = 1 to n (iterate over all rules) 
  1. For j = 1 to i - 1 (iterate over all rules before rule i) 
     1. if Aj has the form `Aj -> d1 | d2 | ... | dn`
       * Replace every production of `Aj -> Ajﬂ` with `Aj -> d1ﬂ | d2ﬂ | ... | dnﬂ`
  2. Eliminate direct left recursion in Ai 

*The inner for look (j) is just "collapsing" rules*




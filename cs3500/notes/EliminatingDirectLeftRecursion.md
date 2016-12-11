# Eliminating Direct Left Recursion 
*α, β are strings of terminals & non-terminals*  

&nbsp; 

#### Definition
Direct Left Recursion takes the following form:    
`A -> Aα1 | Aα2 | Aα3 | ... | Aαn | β1 | β2 | ... βn` 

## Elimination 
To remove direct left recursion: 
1. Rewrite rules of the form `A -> Aα1 | Aα2 | Aα3 | ... | Aαn | β1 | β2 | ... βn` where `βi` does not start with `A`
  1. Use Two rules A and A'  
  `A -> β1A' | β2A' | ... | βnA'`    
  `A' -> α1A' | α2A' | ... | αnA'`


### Example 
Rewrite `A -> Aa | c`   
```
=> A -> cA'
   A' -> aA' | λ
```


### Example 
Eliminate Left Recursion in:    
`E -> E+E | E-E | T`    
`T -> T*T | T/T | F`    
`F -> (E) | int`   


```
=> E -> TE'
   E' -> +TE' | -TE' | λ
   T -> FT'
   T' -> *T' | /T' | λ
   F -> (E) | int
```

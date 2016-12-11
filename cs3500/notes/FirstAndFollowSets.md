# First and Follow Sets 
*Used for Error recorvery in recursive descent parsers*

## First Set 
If α is a string of symbols in an alphabet, then `FIRST(α)` is the set of symbols that start the string. 

Use the following algorithm to find FIRST(β) for any symbol β:   
1. If β is a terminal then FIRST(β) is β
2. If β is a non-terminal, 


### Example 
`S -> aBb | cAd`   
`A -> eA | f`   
`B -> gBh | i`   

Gives the following first and follow sets:   

|Non-Terminal| FIRST | FOLLOW | 
|:-:|-------|-------|
|S| a, c  | $     |
|A| e, f  | d | 
|B| g, i  | b, h |

*FIRST* sets are what comes **before the non-terminal**  
*FOLLOW* sets are what come **after the non-terminal**   

## 


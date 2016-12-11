# Lisp Head First 
Due: December 16th, 2016 11:59:59pm 

Write a collection of LISP function definitions. 



## Submission Guidelines 
Submit via `cssubmit`.   
Your file shall be called “FinalProj.lisp”.    
Your file should include your name.  


## Functions
Your submission file should include definitions for the following lisp functional forms: 

### myLast 
The function `(myLast L)` should evaluate to the last element of the list L     

**Example:** `(myLast '(p a e g)) -> g` 

### myCount
The function `(mycount X L)` should evaluate to the number of occurences of X in the list L.    

**Example:** `(myCount 'a '(p k a t pa e g)) -> 2`


### myGen 
`(myGen X Y)` when given integers X and Y evaluates to the list of increasing integers between X and Y *inclusive* (or nil if such list does not exist).

**Example:** `(myGen 3 11) -> (3 4 5 6 7 8 9 10 11)`    
**Example:** `(myGen 4 4) -> (4)`    
**Example:** `(myGen 11 3) -> ()`   


### myMember
`(myMember X L)` evaluates to `True` if X is in the list L, `False` otherwise.   

**Example:** `(myMember 'a '(p a e g)) -> t`    
**Example:** `(myMember 'b '(p a e g)) -> nil`   



### myCommon
`(myCommon L1 L2)` evaluates to a list of elements that are in both L1 and L2. Assume L1 and L2 have no repeated elements. 

**Example:** `(myCommon '(p a e g) '(a q r e)) -> (a e)` 


### myMap 
`(myMap F L)` should evaluate to the list which results from applying function F to every element in the list L. 

**Example:** `(myMap (lambda (x) (* 2 x)) '(1 2 3 4) ) -> (2 4 6 8)`

### myReduce 
`(myReduce F L)` should evaluate to the result of applying aggregate function F to the elements of L. L will be size >= 2. F will be a commutative function 

**Example:** `(myReduce (lambda (x y) (+ x y)) '(1 2 3 4 5)) -> 15`



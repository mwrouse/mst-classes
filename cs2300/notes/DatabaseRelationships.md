# Database Relationships 
A *Database Relationship* shows a connection between one or more entities. 
 
 ![Relationship example](images/er_diagram1.png)    
In the above example, there are two relationships, *take*, and *of*. 

Students *Take* a Section which is a Section *of* a Course. 

#### Another Example 
![Example showing more complex relationships](images/relationships1.png)  

Drinkers *Like* Beers  
Bars *Sell* Beers at a certain *price*    
Drinkers *Frequent* Bars   


## Multiple Relationships 
Relationships can be tied to more than two entities (these are said to be *not binary relationships*)    
![Non-Binary Relationship](images/relationships2.png)    

Drinkers *Prefer* Bars   
Drinkers also can *Prefer* Beers   


## Relationship Cardinality 
The *Cardinality* of a relationship is the number of occurrences in one entity that can be associated with a number of occurrences in another.  

## One to One 
A *One to One* cardinality means that an entry in one table can only be associated with *one* entry in another table.  

![One To One](images/onetoone.png)  

*One* Student can have *One* *Parking Pass*. And *One* *Parking Pass* can belong to only *One* Student. 

## One to Many 
A *One to Many* relationship means that one entry in a table can be associated with *many* entries in another table. 

![a one to many relationship](images/onetomany.png)   

The *1* and the *m* mean a one to many relationship.   

*One* Advisor can *Advise* *Many* Students   


## Many to Many 
*Many to Many* relationships can have multiple entries be associated with many entries in another table.  

![Many to Many Relationship](images/manytomany.png)  

*Many* Students can *Take* *Many* Courses, and Courses can be taken by *Many* Students.   


## Attributes and Relationships 
Attributes that go on a *many to many* relationship can be placed on **any entity in the relationship, or on the relationship**   

Attributes on a *many to one* relationship **must be placed on the many side entity**. 


## Relationship Participation 
*Participation* of a relationships is a constraint that defines if each entry in a table must be apart of a relationship. 

### Total Participation 
*Total Participation* means that every entry in an entity must be apart of the relationship. 

![Total Participation](images/totalparticipation.png) 

Students **must** *Take* a Course, but Courses do not have to be taken by Students. 

*Total Participation is symbolized as a double line on a diagram. *


### Partial Participation 
*Partial Participation* means entries do not have to have a relationship, and they are indicated by a *single* line on a diagram. 

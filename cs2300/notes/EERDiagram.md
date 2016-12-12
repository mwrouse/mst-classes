# Enhanced ER Diagrams (EER) 
The *Enhanced/Extended ER Diagram* is an extension of the basic ER diagram which adds features for more complex modeling.  

### New Features 
The EER diagram adds:    
**Subclass** and **Superclass** relationships       
**Specialization** and **Generalization**    

## Subclass/Superclass   
Said to be a "is a" relationship.    

![Superclass and Subclass](images/classes.png)  

Employee is the Superclass    
Manager, Engineer, and Secretary are Subclasses        

In this case, Employee can be apart of multiple subclasses. 

A `U` on the relationship line symbolizes subclass and superclasses, the `U` open ups towards the superclass.   

### Disjoint and Overlap 
*Disjoint* and *Overlap* are terms used to describe how an entity can be in a superclass and subclass 

#### Disjoint
*Disjoint* means that the superclass can only be in **one** subclass 

![Disjoint](images/disjoint.png)

#### Overlap 
*Overlap* means the superclass can be in **one or more** subclasses.     

![Overlap](images/overlap.png) 


## Specialization and Generalization 
Normally, Subclasses inherit attributes from their superclasses. 

*Specialization* is a **top-down** approach, means to create a subclass with common attributes from the superclass     

*Generalization* is a **bottom-up** approach, means to create a superclass based on common attributes from existing entities. 


## Example 
This more complex example shows that you can also have *participation* with subclasses and superclasses 

![Complex EER Example](images/EERexample.png)   

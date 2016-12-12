# Data Models
A *Data Model* is an **abstract representation** that **describes a DB structure** and **hides low level details**, but **shows relationships and constraints**. 

## Conceptual Data Model 
The Conceptual Data Model is the *highest level of abstraction* for a database, and is meant to be understood by *non-technical users* 

### Entity-Relationship Diagram 
The Entity-Relationship Diagram (ER Diagram) is a type of Conceptual Data Model.     
![ER Diagram Example 1](images/er_diagram1.png)   

## Implementation Data Model 
The Implementation Data Model (a.k.a, Representational Data Model) is a *not-so-high-level abstraction* of a database, but still meant to be understood by *non-technical users*. 

### Relational Model 
The Relational Model is a type of Implementation Data Model.     

**Student**     

| Name | *ID* | Address | Department |
|------|--------|---------|------------|


**Course**    

| Name | *CourseNum* | Instructor|
|------|--------|---------|


## Physical Data Model 
The Physical Data Model is meant for *technical users*, and shows exactly how data is stored, including data types. 

|*Student*| 
|-----------|
|Name: varchar|
|**ID**: int |



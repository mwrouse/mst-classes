# Databases 
A *database* is a collection of related date. 

*Data* is known facts that can be recorded and has an implicit meaning.

A *Database Management System (DBMS)* is a software package/system that allows for easy interaction with the underlying database. 

A *Database System* is the DBMS combined with the data behind it. 

## Database Users 
*Actors* - users who use and control database content    
*Workers* - users who design and develop DBMS software    

### Actors 
* Designers 
* End Users 
* Administrators 

## DBMS Functionality 
A DBMS can *Define* a database in terms of its data,    
*Construct* or load initial content,    
*Manipulate* the database and its data,    
and *Process and Share* data by a set of concurrent users and applications.


## Database Structure 
A database is composed of *entitities/tables* which represent one group of related data. 

In an entity there exists *attributes/columns* which further refine the description of what the data is in the entity.


## Database Architecture 
A *Schema* is a database design model, a **description** of a database. 

### 3-Schema Architecture 
*Internal Schema* - Physical Data Model     
*Conceptual Schema* - Implementation Data Model    
*External Schema* - Views seen by the user 

#### Definitions
*Logical Data Independence* is the ability to change the conceptual schema without changing views  

*Physical Data Independence* is the ability to change the physical schema without changing the conceptual schema. 


## Database States 
A *Database Instance* is a "snapshot" of a database at an particular moment (snapshot of the State). 

The *Database State* is the data inside of a database at any particular moment. 

The *Initial Database State* is data put into a database at creation. 

A *Valid State* is any state that satisfies constraints/restrictions placed on a database.

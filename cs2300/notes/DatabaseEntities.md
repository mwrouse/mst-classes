# Database Entities 

## Entities
An *Entity* is a table in a database, an *entity set* is a group of entities.        
![Entities are drawn as rectangles with the name in the center](images/entity.png)   


## Attributes 
An *Attribute* is a column inside of an entity.    
![Attributes are drawn in ovals with the name in the middle, attached to the entity with a line](images/attributes.png)


### Composite Attributes 
A *Composite Attribute* is an attribute with multiple parts (e.g., name can be split into first and last names)    
![Composite attributes are drawn as attributes with attributes attached to them](images/compositeattributes.png)   

### Complex Attributes 
A *Complex Attribute* has multiple values, each value is also a composite attribute.     
![Complex attributes are attibutes (double lined oval) with attribtues attached to them](images/complexattributes.png)      


## Keys 
Every entry (row) in a database must have a **unique identifier** called the *key*.       
![Keys are drawn as attributes with the name underlined](images/keys.png)   

### Composite Keys
A *Composite Key* is two or more attributes that, when combined, form a unique value for every entry in a table.     
![Composite keys are drawn as all the members of the composite key as keys](images/compositekeys.png) 

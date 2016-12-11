# Recursive Descent Parser 
A Recursive Descent Parser (RDP) is a LL(k), **top-down** parser 

LL(k) parsers work on *LL grammars*

*RD Parsers can handle ambiguity*

*LL grammars are more restrictive than LR grammars* 

*RD Parsers fail on left recursion*

#### Terminology 
*LL* means left to right and left most derivation 

*Top-Down* parsers begin with start symbol and work way to terminal 

xyzN...    **What to rewrite N as?**

*xyz* have already been converted from terminals to non-terminals 

*...* represents the rest of the unread input

### Writing RDP Code 
* One function per non-terminal 
* Global variable to store next token in input
* Function to read next token into global variable

**Code for RDP parsers can be automagically generated**

#### Example 
Write code for the following grammar: 

S -> dAc | b 

A -> bAB | λ

B -> aS

```cpp
// Checks if input matches S 
void is_S() { 
	if (token == 'd') { 
		get_token(); // Consume next token 
		is_A(); // Check if token read is an A 
		if (token == 'c') { 
			get_token(); 
		} else { 
			error(); // Invalid syntax
		}
	} else if (token == 'b') { 
		get_token();
	} else { 
		error(); // Invalid syntax
	}
}

void is_A() { 
	if (token == 'b') { 
		get_token(); // Consume next token 
		if (token == 'b') { 
			get_token(); 
			is_B();
		} else { 
			error();  // Invalid
		}
	}
}


void is_B() { 
	if (token == 'a') { 
		get_token(); // Consume next token 
		is_S(); 
	} else { 
		error(); // Invalid syntax 
	}
}

vod main() { 
	get_token(); // Get first token 
	is_S(); // S is the start symbol 
	
	if (token == EOF) {
		cout << "Accepted" << endl;
	} else { 
		cout << "Not Accepted" << endl;
	}
}
```



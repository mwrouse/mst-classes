# My First Lexical Analyzer 
 Due: September 30th, 2016 11:59:59pm 

## Submission Guidelines 
Submit through the UNIX systems using the command ‘`cssubmit 3500 a 1`’.

Your program should be in a language and version available in the Computer Science department's UNIX systems.

If your submission is in C, C++, Java, Python 2 or Python 3, your main filename should be called ‘`mylexer.X`’ where `X` is the extension appropriate to your programming language. { `.c`, `.cpp`, `.java`, `.py`, `.py3` }. 

If you choose to submit in another language, make sure it runs in our Unix systems, and submit a make file that generates the necessary executable that will be tested using the command  `./mylexer < testinput.txt`.


## Description 
Write a Lexical Analyzer to recognize Integers, Decimal numbers, Scientific numbers, Hexadecimal Numbers, Phone Numbers, Keywords and Identifiers. 

**Integers** are non-empty sequences of digits optionally preceded with either a ‘`+`’ or ‘`-`’ sign.       
**Decimal** numbers are Integers followed by a ‘`.`’, followed by a non-empty sequence of digits. (e.g. `3.14`, `00.01`, `123.0`).       
**Scientific** numbers are Decimal numbers followed by the character ‘`E`’, followed by a non-zero integer. (e.g. `12.0E4`, `1.23E-6` ).       
**Hexadecimal** numbers are non-empty sequences of digits or the characters ‘`A`’, ‘`B`’, ‘`C`’, ‘`D`’, ‘`E`’ or ‘`F`’ followed by the suffix ‘`H`’. (e.g. `12AD0H`, `123H`, `1A2B3CH`).       
**Phone Numbers** are sequences of 10 digits separated in one of the following formats: *ddd.ddd.dddd* , *(ddd)ddd-ddd* or *ddd-ddd-ddd* where d is a single digit. (e.g. `555.923.0100`,  `101-555-1111`,  `(123)456-7890` ).       
**Keywords** are specific strings that form the language. For this homework we will consider the the following keywords: ‘`while`’, ‘`else`’, ‘`end`’, and ‘`print`’.       
**Identifiers** are strings that consists of a letter followed by zero or more letters, digits or the underscore; and that are not hexadecimal numbers (e.g. `x`, `size`, `name`, `p3`, `r_val` ).       

**Manually** encode the automata using the automata encoding techniques used in class. 

**Do not use a pre-existing regular expression library. **  



## Input 
The first line will be a positive integer N, followed by N strings to recognize, one per line.

## Output 
The first line of the output should echo the number of input lines N. For every line of input, your program should output the line number and state if the string is recognized as either a Keyword, an Identifier, an Integer, a Decimal number, a Scientific number, Hexadecimal number, a phone number, or an invalid string, in the **format** shown in the sample output.

## Sample 
**Input:**        
```
14
83462
-39874.454
while
ABCH
+234.34E-941
124.235.234
color
-1.23E-3.5
4.
+0
(111)111-1111
FFFF
for4
3dfx
```

**Output:**       
```
14
1: Integer.
2: Decimal.
3: Keyword.
4: Hexadecimal.
5: Scientific.
6: INVALID!
7: Identifier.
8: INVALID!
9: INVALID!
10: Integer.
11: Phone.
12: Identifier.
13: Identifier.
14: INVALID!
```

## Hint 
```cpp 
#include <iostream>
#include <string>
using namespace std;


int main ()
{
    int T;
    string s;
    
    cin >> T;    
    for (int i=0; i<T; i++){
        cin >> s;
        cout << "Hello " << s << “!” << endl;
    }
    return 0;
}
```

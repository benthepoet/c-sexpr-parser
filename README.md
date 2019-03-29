# C S-expression parser
This project is an s-expression parser written in C. I wrote this parser in order to read configuration 
files as s-expressions rather than relying on XML or JSON. When run the parser generates a binary tree in memory that represents the s-expression.

The supported datatypes are as follows.
* LIST: `(1 2 3)`
* STRING: `"ABC"`
* SYMBOL: `abc-def` `:key`

The parser will also read numbers but currently they are tagged as `SYMBOL`. The user is 
responsible for the conversion to the appropriate datatype. 

## Getting started
To run the example application, which reads an s-expression from a file and then prints out the contents, run the following.

```bash
mkdir bin
make
./bin/main
```

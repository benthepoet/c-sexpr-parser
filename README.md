# Parsing S-expressions in C
This project is an s-expression parser written in C. I wrote this parser because 
I wanted to be able to store configurations as s-expressions over JSON or XML. 
When run the parser generates a binary tree in memory that represents the s-expression.

The supported datatypes are as follows.
* LIST: `(a b c)`
* STRING: `"abc"`
* SYMBOL: `abc` `abc-def`
* INTEGER: `-123` `456`
* FLOAT: `-0.123` `4.567` 

## Getting Started
To run the example application, which reads an s-expression from a file and then prints out the contents, run the following.

```bash
mkdir bin
make
./bin/main
```

## Known Issues and Limitations
* The parser is not capable of reading escaped characters in strings. I have no plans to address to this as my use case does not require this feature.
* The parser has a 511 character limit on symbols, integers, floats, and strings. This can be increased by changing the `BUFFER_SIZE` macro.

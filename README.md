# Parsing S-expressions in C

[![Build Status](https://travis-ci.com/benthepoet/c-sexpr-parser.svg?branch=master)](https://travis-ci.com/benthepoet/c-sexpr-parser)

This project is an s-expression parser written in C. I wrote this parser because 
I wanted to be able to store configurations as s-expressions over JSON or XML. 
When run the parser generates a binary tree in memory that represents the s-expression.

The supported datatypes are as follows.
* LIST: `(a b c)`
* STRING: `"abc"`
* SYMBOL: `abc` `abc-def`
* INTEGER: `-123` `456`
* FLOAT: `-0.123` `4.567` 

## Running tests
The s-expression used for testing is located at `test/data.lisp`. To execute the tests run the following commands.

```bash
mkdir bin
make
./bin/main
```

## Known Issues and Limitations
* The parser is not capable of reading escaped characters in strings. I have no plans to address to this as my use case does not require this feature.
* The parser has a 511 character limit on symbols, integers, floats, and strings. This can be increased by changing the `BUFFER_SIZE` macro.

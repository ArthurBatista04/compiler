    ## Tiger-Compiler MIPS-32

Codes and Exercises in book << Modern Compiler Implementation in C >>

![compilerbook](https://images-cn.ssl-images-amazon.com/images/I/41ui4h4faGL._AA218_.jpg)

## About

Tiger compiler is a compiler for the tiger language.

Tiger is designed for studying the theory of compiler. More details for the language is described in the book's content and appendix.

## How to use

- make

- ./tc -h

## Options

- Usage: ./tc [flags]
  - -h prints this usage guide
  - -p sets the input file path
  - -a prints the abstract syntax tree
  - -i prints the intermediate representation
  - -c prints the canonical intermediate representation tree
  - -s prints the generated assembly code before regs allocation

## Remark

All tests worked except project 3's test number 10.

## New feature

Boolean (true and false)

Ex: 
- `if (true) then 10 else 20`

- `while (true) do (print("Hello world"))`

## Reference

https://github.com/cmcl/tiger

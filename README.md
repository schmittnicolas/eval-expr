# eval-expr
School project at EPITA

# EvalExp
Goal:
evalexpr is a program that reads on the standard input an arithmetic expression and writes the result
of that expression on the standard output. The input will be of arbitrary size and can be given in
reverse polish notation (RPN) or standard (infix) notation.\

# Valid Expression in standard notation
The expression will be given using infix notation, with the properties that you already know.\
These expressions will contain:\
• Whitespaces (as recognized by isspace(3))\
• Numbers in base 10 (digits from 0 to 9)\
• The unary identity operator: +\
• The unary negation operator: -\
• The binary addition operator: +\
• The binary subtraction operator: -\
• The binary multiplication operator: *\
• The binary division operator: /\
• The binary modulo operator (the one from C language): %\
• The binary exponentiation operator: ^\
• Left and right parenthesis: ( and )\
Here is a list of these operators from highest to lowest priority:\
• Parenthesis ( and ), non-associative\
• Unary + and -, right-associative\
• ^, right-associative\
• *, /, %, left-associative\
• Binary + and - left-associative

# Usage
Compile the project with 
```bash
make
```
To run the project
```bash
echo "expression" | ./evalexpr
```
Or (in rpn notation)
```bash
echo "rpn-expression" | ./evalexpr -rpn
```

## Clean project
To clean the project:
```bash
make clean
```

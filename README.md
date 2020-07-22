# Big Number Calculator In C

An 16-bit integer can hold values upto 2^15-1, thus any operation resulting in a value greater than the INT MAX will overflow and result in a garbage value thus I implemented a Big Number Calculator in C which calculates addition, subtraction, division, power, square root, absolute value of numbers with any amount of digits.

This is done with the help of character arrays, since character arrays don't have a limit to how many characters they can hold(unless the stack size exceeds 1MB). 

_ It can handle negative numbers and decimal points as well._

To execute the commands-

(Keyword)(SPACE)(number1)(SPACE)(number2)
  
 ### The Keywords are:
 
 * Addition - ADD
 * Subtraction- SUB
 * Division- DIV
 * Multiplication - MULT
 * Absolute - ABS (Note: In absolute value there will only be one number)
 * Power- POW
 * Square Root - SQRT(Note: Uses only one number)

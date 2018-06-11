# inputs
inputs are read from file "input.txt"

a = 3 ;

b = 2 ;

c = a + b * 4 ;

b = c + b * 2 ; //the value of b changes after reading this line

d = a * ( b - c ) / 2 ;



# outputs

c = a * ( b + 4 ) ;

Postfix:a       Stack:Empty

Postfix:a       Stack:*

Postfix:a       Stack:*(

Postfix:ab      Stack:*(

Postfix:ab      Stack:*(+

Postfix:ab4     Stack:*(+

Postfix:ab4+*   Stack:Empty


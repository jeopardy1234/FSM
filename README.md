# Finite State Machine
## Minimization of DFA
We have to deal with disjoint sets in this problem. 
The algorithm goes as follows:

- Make two disjoint sets - final and non final
- check for each pair of elements in the same set. Check if they are distinguishable.
- If they are distinguishable, then the two elements are in different sets
- If they are not distinguishable, then the two elements are in the same set (for this iteration)
- Let the previous DSU state be $D_x$  and the new one be $D_{x+1}$. Repeat the process until $D_x != D_{x+1}$

### Checking if two elements are distinguishable
Let the two elements transition to x and y after taking a certain input.
If x and y do not belong to the same set then these elements are distinguishable, else they aren't. 







## REGEX to NFA

We use two main ideas here: Shunting Yard algorithm to convert infix string to postfix, and Thompsons algorithm to convert the postfix to NFA.

The main idea behind Shunting Yard is to get rid of those annoying parentheses. It makes processing the string a lot easier.

### Infix to Postfix:

- Maintain an output string and a stack.
- If you encounter an alphabet, push it into the stack
- If you encounter an operator - push/pop according to it's priority

### Postfix to NFA:

- Keep pushing characters into the stack.
- If you encounter '.' or '+', pop off last two elements off the stack and perform the operation. Then push the result into the stack.
- If you encounter '*' pop off the last element from the stack and perform the operation. Then push the result back into the stack.

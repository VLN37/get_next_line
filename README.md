## Get_Next_Line

In [42SP's](42sp.org.br) second project we are tasked to code a function that returns the next line of a file each time it is called.

### What i learned?

This project introduces us to a few new concepts, such as file descriptors. static variables and how they persist throughout function calls, all the while learning about more complex condition structures. Also an opportunity to learn about memory management in C as well as the intricate tools that help you fix them, given the inevitability of doing this project without leaks!

### My badge

![libft badge](/docs/gnlbadge)

### My grade

![libft grade](/docs/gnlgrade)

### How to use

```
/*You need a linux or a mac that is able to compile C programs with clang.
**Program works with redirection of standard input.
*/Examples:

//clone the repository
git clone https://github.com/VLN37/get_next_line.git

//to compile the program
clang get_next_line.c get_next_line_utils.c main.c

//you may cat any file you want but a sample one is included
cat lorem | ./a.out

//you may also write everything you want in heredoc, followed by END and enter in a single line
<< END cat | ./a.out

//you may use my main file to test your own projects!
```

### License

This project is licensed under the MIT terms, available [here](LICENSE)

# BF Interprater
## Summary
This is a simple bf (check out the code or the internet, you will understand what
is ment by "bf")
interprater and shell in one CLI application.

# BF Language
BF is a turing complete, esotaric programming language. Its working consists of
moveing a pointer through a "tape" which is essencially a 100 integer long array.
Through this motion the programmer can
1. decrease the value stored at the current index the pointer point to
    - with the "-" command
    - minimum value is 0 for any element, any further substraction will loop back to 255
1. increase the value stored at the current index the pointer point to
    - with the "+" command
    - maximum value is 255 for any element, any further addition will loop back to 0
1. move the pointer to the right on the tape
    - with the ">" command
    - by default, the maximum index on the tape is 99, any further motion will loop back to 0
1. move the pointer to the left on the tape
    - with the "<" command
    - minimum index is 0, attempt to move the pointer any more to the left will loop back to 99
1. get input from the user
    - with the "," command
    - the result must have a size of 2 bytes
1. print the value currently pointed to
    - with the "." command
    - the integer value stored at the index that is currently pointed to will be converted to a character
1. loop
    - with "[" and "]" characters
    - when the "[" character is reached, will move to the matching "]" if the currently pointed value on the tape is equal to 0
    - when the "]" character is reached, will move the the matching "[" character if the currently pointed value on the tape is not equal to 0

# How To Run A BF File
> the source file for your bf file does not need to have an extention of .bf

```bash
bf_interpreter.exe -f <file name>
```
the above command runs the file named "\<file name\>"

# Shell Mode
If no command line parameters are given, the application will start in the shell mode
In the shell mode, the following commands can be used
- run \<file name\> -> runs the file named "\<file name\>"
- quit -> quits out of the shell
- exe \<code\>  -> executes the bf code that follows the command
- help -> displays help menu

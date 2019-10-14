# Text Spreadsheets
This is a program designed for creating, displaying, and organizing data with spreadsheets.
Keep in mind, I spent only about three days on this so it isn't as advanced or high quality
as Excel or some of the other spreadsheet applications you might use, it's just a demo.
That being said, for those intereseted, here's how to use it:
## Data Input
There are 2 main ways of writing to a cell on a spreadsheet: writing and accessing.
To write something into the spreadsheet the syntax is:

enter *row,column* = *data*

Which is slightly different than a normal input, which would be *column,row*, but I found
usage of this program to be easier for me with this syntax. Also, *data* must be a number,
not a character or a string, simply because you can't use the arithmetic functions (referenced later)
in this program if the data you are using is not numeric. Moving on, accessing a cell's data 
is similar to writing or entering in data, since the parameters are mostly the same:

access *row,column*

Which will print the value of whichever cell you selected as a floating point.

### Examples:

*enter 3A = 45*

This command will write the value 45.00 into cell A3/3A.

*access 3A*

This command will print '45' when entered in.

**NOTE: Entering commands with the wrong syntax will cause program to crash:**
**DON'T:**
~~*enter A3 = 45*~~
~~*enter 3A = HELLO*~~
~~*access A3*~~

## Arithmetic Functions
No spreadsheet tool can be put to good use without the use of functions. With TextSpreadsheets, 
functions use cells and cell locations for parameters:

function *operation* *operator1:(*row,column*)* *operator2:(*row,column*)* *dataIn:(*row,column*)*

Operations include:
1) sum
2) subtract
3) multiply
4) divide
5) power
6) sqrt (square-root)

And adding 'function' in the beginning lets the program know that the following input will
involve arithmetic operation and/or calculation. Here's an example of addition within 
two cells, in this case, 3A/A3 and 3B/B3, whose result will be entered into cell 4C/C4:

*function add 3A 3B 3C*

*or*

  *function
  add
  3A
  3B
  3C*

### Let's take a closer look:

*function* : We have declared that the following input will be part of a function,
*add* : We have also declared more specifically that the following input for the function will be for addition.
*3A 3B 3C* : Finally, we have declared that the addition will occur between the values of cells 3A and 3B, with the result being in the cell of 3C.

And it doesn't have to be just for addition as well; you can replace *add* with the other
functions.

**NOTE: ** For the function "sqrt", the 2nd variable parameter is not taken into account, so just
enter '0A' for that:

*function sqrt 3A 0A 3B* 

**Will result in the square root of 3A being put into 3B**

## File Handling

File handling is much simpler than any of the other commands listed here. There are 4 ways
of handling files with TextSpreadsheets: saving, uploading, editing, and uploading programming
(we'll get to that later). To save a spreadsheet, you must do the following:

save *file_name*

Save your spreadsheet as a text document. An example of a file name may be:

*C:\\\Users\\\Documents\\\spreadsheet1.txt*

**NOTE: Be sure to make the backslashes face the correct way: \\, not /.**

Uploading a spreadsheet is just as easy as saving it. Simply swap the 
*save* keyword for *upload*:

upload *file_name*

## Spreadsheet Programming

When first opening the TextSpreadsheets program, you will be prompted a question:

*Mode (Program/Free Input):*

If you want to use all of the functions and commands mentioned above, enter 'F'.
The other option would be to enter 'P', which would then produce the following 
output:

*Program file: *

This prompt asks for a spreadsheet program file. Creating a spreadsheet program file is 
very easy, since it's literally just putting a list of the commands you want into
one file. For example, here's what an addition program file would look like:

  *3
  enter 3A = 45
  enter 3B = 60
  function sum 3A 3B 3C*

And your file extension would be '.txt'. Let's examine this program:

1. *3* This number is the number of lines in your program, not including this number.
2. *enter 3A = 45* We put 45 into cell 3A/A3.
3. *enter 3B = 60* We also put 60 into cell 3B/B3.
4. *function sum 3A 3B 3C* We put the sum of cells 3A and 3B into cell 3C.

As you can see, creating a program file is as simple as free input. So, to sum up 
this section, here's a quick review:

1. You will be prompted 'Mode (Program/Free Input)', where you will enter
'F' for Free-Input, and 'P' to upload a program file. 
2. If P is entered, then you will be prompted 'Program file: ', where you
will enter the name of the file containing the spreadsheet program.
3. The program will then spit out an output in the form of spreadsheets.

#Additional notes:

This program is written in pure C, so yes, it is compatible on Mac, Windows, and Linux
computers. The only requirement is a C/GNU compiler. This program will (obviously) be 
getting updates and improvements every now and then, and usage of this program (manual above)
will remain the same, so I won't be changing any syntax **unless it makes the program more efficient.**







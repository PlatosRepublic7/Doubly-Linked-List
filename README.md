# Doubly-Linked-List
This program is an attempt at creating a doubly-linked list in C from scratch. The functionality, as well as the efficiency, of this 
implementation is not the best. It is representative of an exercise in creating a dynamic list structure that allows for more utility than otherwise
would be possible with a singly-linked list. 
 
This is tested by means of a simple selection sort algorithm. The gen_nums.c file is able to generate one million non-negative integers in a file
called numarr.txt, which is then parsed and implemented as a DLL struct. The getnum.h header file is there only as an exercise in offloading a 
small amount of code functionality, it is ultimately not important but is required should the main source code, sort.c, is to be run.

The main loop of the program iteratively generates DLL's in powers of 10, and then sorts them. It does this up to one million integers, although it 
should be noted that this final sort may take up to twenty minutes to complete. Therefore I also created a simple progress indicator, by percentage,
for the sorting algorithm. The first progress indicator is for building the unsorted list, and the second is the progress of the sort. The output is
in the terminal.

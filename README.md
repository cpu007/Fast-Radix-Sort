# Fast-Radix-Sort
A small and fast implementation of radix sort for integers in c++. Warning Uses C++11 Features!!!

The cpp file provided is a simple c++ implementation of the popular 
radix sort algorithm, using bit-shifting and bit-masking to speed up 
division of elements into buckets by bypassing slow operations such as that of
modulo.

The main method, provides a command line interface for creating an array of random
integers and then proceeds to sort, afterwards displaying the initial, middle, and end values of the 
array, as well as making a single pass through the array to determine if no elements are out of place
and displays these results to the screen.

The file was compiled using g++ version 4.9.2 on a windows 8.1 pc, with the -O2 flag set for the optimization level
other optimization levels were tested but this seemed to be produce the fastest code. Clang++ version 3.7.1 was also
tested with the same -O2 flag for optimization, and better results were obtained. Of course this is machine dependant
and results may vary.

Feel free to use any code in this file as well as modify it in any way. 
However all credit must be given to the original author: Kenneth Chiguichon.

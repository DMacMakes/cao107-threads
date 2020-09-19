# Quicksort Multi Dimensional

Creates a 2D array (array containing arrays) of unsigned 16 bit (short) integers. A function is then called in a loop, loading **up to 16 text files**, each containing **100,000 random** integers between in the range {0..65535} (see randoms folder).  

### Funky array declarations

It looks weird where the arrays are declared. It uses `**`, and `new`, and the array is initialised on the right side. All possibly new syntax for you guys. On the up side, I've already written it so you don't have to do it from scratch. 

`new` just means to declare the new array on the "heap" a bunch of "dynamic" memory we can use for bigger things. Otherwise they're declared on the "stack", a more controlled bit of memory that c++ uses when it's making functions and local variables. The main bit you need to remember is "when I load big data, I need to use `new` to initialise the variable I'll store it all in".

You can think of a heap as "heaps of space", and a stack as a stack of plates. You have to be a bit careful around the plates and you don't want too tall a stack or it'll.. go badly.

A c style array is a very simple thing: it's basically an address in memory and a data type, say `int`. From there you can use a number in square brackets, say `[10]`, to jump 10 slots along in memory.. and those slots are whatever size an `int` is. A default int is 32 bits on windows.

An array of arrays, then, is a bunch of pointers to pointers. You don't have to really understand this properly, except to say the two star symbols (\*\*) is the 2 in 2D, and the single star (\*) is when we're down to one dimension.

MISSING: Drawing of this stuff
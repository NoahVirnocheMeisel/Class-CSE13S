The overarching program is split up across eight different C files. Mathlib-test.c is the central test harness for the other seven functions and is used to test out all of the different methods for approximating e and pi. The desired methods can be selected by using a variety of different command line arguments which is specified in Asgn2 Section 7.1\cite{Asgn2:pdf}.Aside from these command line arguments, there are no other inputs for the function. 

The format for using a command line argument for this program is as follows(done after you have compiled the program using the provided makefile).

./mathlib-test -"charecter for command"

The output for each functions test is in the following format

Function_Name = Approximation, MathLibrary Value = Approximation, diff = difference.

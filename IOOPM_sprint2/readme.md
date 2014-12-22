Readme for istring Anders Ålander 4 dec 2014
============================================

Commands list
-------------
    make: command to compile the file. \n
    maketest: compiles the program and runs the tests\n
    make clean: removes all generated files\n

Goals 
-----
Z71

Notes
-----
The istring program has been implemented following the istring.h. It has been extended with help functions listed in the istring_rep.h header file. 

NIH and DRY
-----------
Program is reusing code from custom made function whose only purpose is to avoid repetition. It also uses headers from from the c library to avoid having to write the functions again.
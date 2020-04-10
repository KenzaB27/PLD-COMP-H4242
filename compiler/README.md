# C compiler with antlr4/c++

## Instructions

This manual shows how to use our basic C compiler using Antl4 for C++.
In order to compile a ".c" file, we first have to be in the "compiler" folder. The command then to tap is : "./compile_if.sh". This will enable us to compile the "main.cpp" and to produce the executable for our program, called "ifcc". We then implemented different options to launch our program, using the command : "./ifcc -S [-o outputFile] [-Wall]  inputFile"
   * -o outputFile:   -o to choose an output file.
   * -S           :   -S to compile only. 
   * -Wall        :   -Wall for warnings.

We can also run several tests to make sure our compiler is working properly. For that, we have to be in the "tests" folder. The command then to tap is for example "./test_if.sh testUnitaire/testAddition", if we want to execute the addition tests.


## Source Files

* `ifcc.g4` contains the grammar in antlr4 format
* `main.cpp` contains the C++ code to call the antlr4-generated parser on the  file name provided in the command line.
* `visitor.h` is a visitor of the parse tree that produces an assembly-language output

## Compilation scripts

* `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
* `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
* `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.


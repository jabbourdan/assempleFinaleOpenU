# assempleFinaleOpenU

## About ##
This project is an assignment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 15-instruction asssembly language.
For any issues, questions and ideas turn to the Issues tab.

## Task Summary:
Create an assembler for an assembly programming language defined in The Open University (of Israel) System Programming Lab course final project.

##### Implementation Overview and General Approach:

#### Objectives (Goals): ### 
1) memory efficiency: It was important for me to allocate the memory of the binary image output dynamically so that the memory use of the program would be efficient and that the memory allocation of the image the assembler generates would fit the minimum required for compiling source code.

2) Separation of concern:I tried to split the program into independent components that will be responsible for well-defined tasks and that the sharing of data between files will be through some kind of encapsulation method such as state getters/setters and scoping global variables to be static so that they will be scoped to the single file that they belong to.

3) Abstraction of data structures and variables used to fit our needs by defining different typedef structs types enums and constants.

## Source structure (Modules)
1. `assembler` - main function definition, argv & argc processing, single file processing.
2. `first_pass` - contains functions for processing a single line in the first pass and a code line in the first pass.
3. `second_pass` - contains function for processing a single line in second pass and replacing symbol by it's address.
4. `code` - contains useful function for processing code.
5. `instructions` - contains useful function for processing instruction.
6. `globals.h` - contains type and constant definitions.
7. `table` - contains definition of table-like linked list data structure.
8. `utils` - contains general-purposed, project-wide functions.
9. `writefiles` - contains methods for writing output files: `*.ob`, `*.ext` and `*.ent` 



## Build
You may build with several tools:
1. Using CMake: run `cmake --build .` (you might have to run `cmake --cofngiure .` first) - Provides support for CLion IDE
2. Using `make` command (Makefile)
3. Manually (Not recommended): compile each `*.c` file to `*.o` and then compile all to a single executable using `CC`/`GCC`/`CLang` with `-g a.o b.o .... -o exe`

## Usage
`./assembler file1 file2 file3 ...`
Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.

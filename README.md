# TTC_simulation
This is a simulation of the Bloor-Danforth [TTC](http://www.ttc.ca/) subway line in C. The subway line is simulated as a linear structure, giving rise to the linked list data structure used in the projet. 

This project was implemented as a CSC190 course project at the University of Toronto in winter 2013. You can learn more about the project goals and requirements [here](http://www.cs.toronto.edu/~patitsas/cs190/lab3.html) and [here](http://www.cs.toronto.edu/~patitsas/cs190/lab4.html). 

## Installation
Navigate to the directory you want to clone the project to. Clone the repo using the following git bash command
```
git clone https://github.com/tarhang/TTC_simulation.git
```

## Usage

* `ttc.h` - contains data structure definitions and function headers.
* `passengers.c` - contains the implementation of methods related to the passenger data structure (passengers are implemented using linked lists).
* `trains.c` - contains the implementation of methods related to train data structures (linked list).
* `stations.c` - contains the implementation of methods related to station data structure (doubly linked list).
* `bloor_line.txt` - input data containing the names of the stations along the subway line
* `test_passenger.c`, `test_train.c`, and `test_station.c` - each contain a main function to test the methods in their corresponding algorithm files.
* `Makefile` - contains the command-line compilation instructions to test the code. There are three compilations in the file:
  * type `make passenger` in the command-line to create an executable file to test the methods in `passengers.c`. This creates an executable file name 'passenger'. Run the executable by `./passenger` in the command-line.
  * type `make train` in the command-line to create an executable file to test the methods in `trains.c`. The executable is then run by the command-line instruction `./train`.
  * type `make station` to create an executable to test the methods in `staions.c`. Run the executable with `./station`.

# EX3: Flight Simulator

"EX3: Flight Simulator" can control a FlightGear flight simulator based on instructions given by a text file of flight instructions. "EX3: Flight Simulator" supports basic variable assignments, conditionals (if, while), and handles the communication with the simulator.

## Installation and Prerequierments

Please make sure you have the following installed before atempting to run "EX3: Flight Simulator":
1. g++ (compiler for C++)
2. FlightGear 2019

In FlightGear:
got to settings and under additional settings paste:
--telnet=socket,in,10,127.0.0.1,5402,tcp 
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small

## Usage

From the directory in which the program's files are located move the file generic_small.xml to the file ‫‪data/protocol‬‬ in the location where FlightGear is installed (this action has to be performed once).

- Compile using:
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

- Place your instruction file "file_name.txt" in the same directory as the compiled program a.out.
- Open Terminal in the directory of your compiled program and type:
./a.out "file_name.txt"

if the following output is printed, you can open the FlightGear GUI:
waiting 1 minutes for gui
Server is now listening ...

Now all that's left is to sit back and enjoy the flight.

## Contributing
Osher Zizemski
Hadar Reuven

Project on GitHub:
https://github.com/ZizOsher/EX3-Flight-Simulator

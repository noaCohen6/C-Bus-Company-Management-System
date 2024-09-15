# Bus Company Management System

## Project Overview
This C project implements a comprehensive management system for a bus company. The system handles various aspects of the company's operations, including buses, routes, drivers, bus stops, and passengers. This project is developed using Visual Studio.

## Development Environment
- Language: C
- IDE: Microsoft Visual Studio

## System Components
The system manages the following entities:

1. **Station**: Represents a bus stop with a name and number.
2. **Bus**: Represents a bus with license number, seat capacity, and potential faults.
3. **Fault in Bus**: Represents different types of bus faults and their repair costs.
4. **Driver**: Represents a bus driver with name, ID, salary, seniority, and trip count.
5. **Passenger**: Represents a passenger with name, ID, and ticket type.
6. **Line of Travel**: Represents a bus route with associated bus, driver, passengers, and stops.
7. **Bus Company**: The main entity that contains all buses, drivers, stations, and lines.
8. **Date**: Represents a date with day, month, and year.

## Features
The system provides the following functionalities:

0. Upload System From Text Or Binary File
1. Print Bus Company
2. Add Station
3. Add Bus
4. Add Driver
5. Add Line
6. Add Passenger To Line
7. Add Fault To Bus
8. Remove Fault From Bus
9. Add Station To Line
10. Remove Station From Line
11. Sort Lines
12. Search Lines
13. Calculate Company Profit
14. Find The Driver With The Most Trips
-1. Exit And Free memory

## Binary File Compression
The system implements binary file compression for the Station structure:
- Station Name: Compressed to 9 bits (length without null terminator)
- Station Number: Compressed to 7 bits

## How to Use
1. Open the project in Visual Studio.
2. Build the solution to compile the project.
3. Run the program from within Visual Studio or navigate to the output directory and run the executable.
4. Follow the on-screen menu to interact with the system.
5. To exit the program and free allocated memory, select option -1 from the menu.

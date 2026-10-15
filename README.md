# Vehicle Rental Management System

## Overview

This project is a C++ vehicle rental management application developed using Qt 6. It demonstrates object-oriented programming principles through a desktop application designed to manage vehicle information and different vehicle types.

The project uses inheritance and polymorphism to organise vehicle classes and Qt Widgets to build the graphical user interface.

## Features and Concepts

- **Object-oriented design:** Organises the application using classes and objects.
- **Encapsulation:** Uses a base `Vehicle` class to represent vehicle information.
- **Inheritance:** Extends the base vehicle class to represent cars and motorcycles.
- **Polymorphism:** Applies polymorphic behaviour where supported by the class implementations.
- **Vehicle information:** Represents properties such as brand, model, ID, rental price per day, and rental status.
- **Graphical user interface:** Uses Qt 6 Widgets to develop the desktop interface.

## Technologies Used

- C++
- Qt 6
- Qt Widgets
- CMake
- Object-oriented programming

## Project Structure

| File | Description |
|---|---|
| `main.cpp` | Application entry point. |
| `Vehicle.h` | Declaration of the base vehicle class. |
| `Vehicle.cpp` | Implementation of the base vehicle class. |
| `CarMotorcycle.h` | Declarations related to cars and motorcycles. |
| `CarMotorcycle.cpp` | Implementations related to cars and motorcycles. |
| `VehicleRentalWindow.h` | Declaration of the graphical user interface class. |
| `VehicleRentalWindow.cpp` | Implementation of the graphical user interface. |
| `CMakeLists.txt` | Defines the project configuration and build instructions for CMake. |

## Learning Objectives

This project provides practical experience with:

- Classes and objects
- Encapsulation and inheritance
- Polymorphism and virtual functions
- C++ header and implementation files
- Qt Widgets and graphical user interface development
- CMake project configuration

## Building the Project

The project uses CMake and requires Qt 6.5 or newer, including the Core and Widgets modules.

To build the application, open the project in Qt Creator, configure a suitable Qt kit, and build the project using the included `CMakeLists.txt`.

## Purpose

The purpose of this project is to apply C++ programming and object-oriented design principles to a practical vehicle rental scenario while gaining experience developing desktop applications with Qt 6.

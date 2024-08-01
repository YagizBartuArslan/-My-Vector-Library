# -My-Vector-Library
# Overview
This project implements a templated vector library in C++, named myVector, which supports various data types and key-value pairs. It includes functionalities to manipulate and process vectors, including operations such as pushing, removing, finding, copying, and replacing elements. The library also supports data processing for different types, including strings and arithmetic types.
# Features
* Templated Vector Class: Supports multiple data types for both keys and values.
* Iterator Class: Provides easy traversal and manipulation of vector elements.
* Basic Operations: Push, remove, find, replace value, replace key, and check equality.
* Data Processing: Specialized functions for processing string and arithmetic data.

# Usage
# Including the Library
To use the myVector library, include the header file in your project:
  #include "myVector.h"
# Creating a Vector
You can create vectors with different data types for keys and values:
  myVector<std::string, int> vecStringInt;
  myVector<double, double> vecDoubleDouble;
  myVector<int, std::string> vecIntString;
  myVector<double, std::string> vecDoubleString;

# Basic Operations
# Push
To add elements to the vector:
  vecStringInt.push_back("Hello", 1);
  vecDoubleDouble.push_back(22.2, 2.2);
  vecIntString.push_back(100, "key1");
  vecDoubleString.push_back(3.5, "key3");

# Remove
To remove elements from the vector by key:
  vecStringInt.remove(1);
  vecDoubleDouble.remove(2.2);
  vecIntString.remove("key1");
  vecDoubleString.remove("key3");

# Find
To find elements in the vector by key:
  std::string* value = vecStringInt[1];
  if (value) std::cout << "Found: " << *value << std::endl;

  double* value = vecDoubleDouble[2.2];
  if (value) std::cout << "Found: " << *value << std::endl;
  
# Replace Value
To replace values in the vector by key:
  std::string* value = vecStringInt[1];
  if (value) *value = "NewValue";

  double* value = vecDoubleDouble[2.2];
  if (value) *value = 33.3;

# Replace Key
To replace keys in the vector:
  myVector<std::string, int>::Iterator itr = vecStringInt.begin();
  itr.find(1, vecStringInt);
  itr.replaceKey(2);

# Check Equality
To check if two vectors are equal:
  if (vecStringInt == vecStringInt2) {
    std::cout << "Vectors are equal" << std::endl;
  } else {
    std::cout << "Vectors are not equal" << std::endl;
  }
# Data Processing
The library supports processing string and arithmetic data: 
  vecStringInt.process_data();
  vecDoubleDouble.process_data();
# Example
An example of how to use the myVector library is provided in main.cpp. The example demonstrates creating vectors, performing operations, and processing data.

# Author
Yaðýz Bartu Arslan

Junior Computer Science & Engineering Student at Sabanci University
Written on: 02.12.2023
# Files
myVector.h: Header file containing the definition of the myVector class.
main.cpp: Example usage of the myVector library.
input1.txt, input2.txt, input3.txt, input4.txt: Sample input files to test the functionalities of the myVector library.

# Description
This C++ project is focused on the implementation and management of a B-tree data structure to facilitate efficient data retrieval and manipulation of a simulated database. It primarily caters to managing two types of data: customer and their account information, structured in CUSTOMER and CUSTOMER_ACCOUNT tables respectively. 

The project's key feature is its use of a B-tree of customizable order (between 3 and 10) as an indexing method for the CUSTOMER_ACCOUNT table, significantly enhancing search performance.

> This project was developed as [the second university assignment](instructions.pdf) for "Algorithms and Data Structures 2", University of Belgrade School of Electrical Engineering majoring Software Engineering. Please refer to the instructions for detailed assignment instructions.

# Project Overview
This C++ project implements a B-tree data structure for efficient searching and managing data from two tables: CUSTOMER and CUSTOMER_ACCOUNT. This is part of a course assignment for Algorithms and Data Structures 2.

# Interactive Menu 
Users interact through a menu to execute operations like creating, destroying, and displaying the index, adding and deleting records, and fetching user data.
B-tree Implementation: A B-tree of order m (3 ≤ m ≤ 10) is used as an index for the CUSTOMER_ACCOUNT table.

# Efficient Data Retrieval: 
The project efficiently retrieves user and account information using the B-tree index.

Data Input Flexibility: Data can be entered either through standard input or by reading from a file.

Robust Error Handling: The program is resistant to errors and provides clear notifications in case of error detection.

# Features
Create/Delete Index: Create or destroy a B-tree index for the CUSTOMER_ACCOUNT table.

Display Index: Output the B-tree index to the standard output.

Search User Data: Enter a user's C_ID to fetch and display their information and associated accounts.

Add Record: Add a new account record to the index.

Delete Record: Remove a specific account record from the index.

Delete User Accounts: Remove all account records associated with a given user.


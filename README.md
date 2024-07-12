
# Online Library Management System

The Online Library Management System is a robust application designed to handle multiple clients simultaneously. This system leverages file locking, file handling, multithreading, and interprocess communication to ensure seamless and efficient management of library resources.






## Project Overview

The Online Library Management System is developed to automate and streamline the processes involved in managing a library. It supports concurrent access by multiple clients, ensuring data integrity and consistency through advanced programming techniques.



## Features

- Concurrent Client Handling: Supports multiple clients accessing the system simultaneously.
- File Locking: Ensures data integrity by preventing simultaneous writes to the same file.
- File Handling: Efficient management of library records through file operations.
- Multithreading: Utilizes multiple threads to handle different clients and operations concurrently.
- Interprocess Communication (IPC): Facilitates communication between different processes of the system.



## Architecture

The system is built using the following components:

- Client Module: Handles user interactions and sends requests to the server.
- Server Module: Manages requests from multiple clients, performs operations, and ensures data consistency.




## Client Operations
### Logging In

Clients must first log in as either an admin or a user, or register a new account.

- Login as Admin or User
- Register a New Account
- Forgot Password

### Admin Operations

Once logged in as an admin, the following operations are available:

- Add a Book
- Add a User
- Remove a Book
- Remove a User
- Search for a Book
- Search for a User
- Update the Quantity of a Book

### User Operations

Once logged in as a user, the following operations are available:

- Borrow a Book
- Return a Book
- View All Books
- Search for a Book

## Server Operations

- Handle Client Requests: Accept and process requests from multiple clients concurrently.
- Manage Records: Ensure data consistency and integrity through file locking and file handling techniques


# Library Management System

## Project Description
The Library Management System is a console-based application developed using C programming. It helps manage library book records and handles book issuing and returning operations.

The application allows users to add, view, remove, and search for books. It also maintains issued book records, user details, and issue and return dates. File handling is used to store book and issue information permanently.

## Technologies Used
- C Programming
- Structures
- Arrays
- Functions
- File Handling
- String Handling
- Date and Time Functions

## Features

### Book Management
- Add new books with Book ID, Title, Author, and Quantity.
- View all available book records.
- Search books by title.
- Remove book records using Book ID.

### Book Issue Management
- Issue books to users.
- Store User ID and User Name.
- Automatically record the book issue date.
- Reduce the available book quantity when a book is issued.

### Book Return Management
- Return previously issued books.
- Automatically record the return date.
- Update the available book quantity after returning a book.

### Issued Book Records
- Display issued book details.
- View user information.
- Track issue dates and return status.

### Data Storage
- Store book information in `books.txt`.
- Store issued book information in `issues.txt`.
- Save and load records using file handling.

## How to Run the Project

### Step 1: Download or Clone the Repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### Step 2: Open the Project Folder

Open the downloaded project folder in your preferred code editor or terminal.

### Step 3: Compile the C Program

```bash
gcc library.c -o library
```

### Step 4: Run the Program

**Windows:**
```bash
library.exe
```

**Linux:**
```bash
./library
```

## Main Menu

The application provides the following menu options:

1. Add Book
2. View Books
3. Remove Book
4. Search Book
5. Issue Book
6. Return Book
7. List Issued Books
8. Save
9. Exit

## File Structure

```text
Library-Management-System/
│
├── library.c
├── README.md
├── books.txt
├── issues.txt
└── screenshots/
```

Note: `books.txt` and `issues.txt` are created when the application saves data.

## Concepts Learned
- Structures and Arrays in C
- Functions and Modular Programming
- File Handling
- String Manipulation
- Date and Time Handling
- Conditional Statements and Loops
- Record Management

## Future Enhancements
- Add book availability reports.
- Implement actual due-date calculation.
- Add overdue fine calculation.
- Add user login and authentication.
- Improve input validation and duplicate book ID handling.

## Author
Himasri paluru

# Library Management System - AI Coding Guidelines

## Architecture Overview
This is a console-based C application for managing library books and users. The system uses binary file storage for persistence instead of a database.

**Key Components:**
- `book.c`: CRUD operations for books (add, edit, delete, display)
- `user.c`: CRUD operations for users
- `borrow_return.c`: Handles book borrowing and returning logic
- `lookup_display.c`: Search and display functionality
- `menu.c`: Console menu system and main navigation

**Data Storage:**
- Books: `./data/libraryBook.dat` (struct book {int id; char title[100]; char author[50]; int status;})
- Users: `./data/libraryUser.dat` (struct user {int id; char name[50];})
- Borrows: `./data/borrowBook.dat` (struct borrow {int userId; int bookId;})

**Data Flow:**
- All operations read/write binary files directly using FILE* and fread/fwrite
- Book status (0=available, 1=borrowed) is updated in place
- Deletes use temp file rewrite pattern (read original, skip deleted record, write to temp, rename)

## Build and Run
Compile with GCC: `gcc -Wall -Wextra -g3 src/main.c -o output/main.exe`
- Note: `main.c` includes `menu.c`, which includes all other .c files, so single-file compilation works despite non-standard includes
- Standard approach would be separate compilation: `gcc -c src/*.c -I include/` then `gcc *.o -o output/main.exe`

Run: `./output/main.exe` from project root

## Code Patterns
**File I/O Pattern:**
```c
FILE *file = fopen("./data/libraryBook.dat", "rb");
if (file == NULL) { printf("Can't open file!\n"); return; }
// ... operations ...
fclose(file);
```
- Always check fopen return value
- Use binary modes ("rb", "wb", "ab", "rb+") for struct I/O
- Close files immediately after use

**Input Handling:**
- Use `scanf("%d", &var)` for integers, followed by `getchar()` to consume newline
- Use `fgets(buffer, size, stdin)` for strings, then `strcspn(buffer, "\n") = '\0'` to remove newline
- Validate scanf return value: `if (scanf("%d", &var) != 1) { error handling }`

**Struct Updates:**
- For in-place edits: `fseek(file, -sizeof(struct), SEEK_CUR); fwrite(&struct, sizeof(struct), 1, file);`
- For deletes: Read all records, skip target, write to temp file, then rename

**Menu Navigation:**
- Recursive menu calls (e.g., `return menu();` to go back)
- Switch statements for option handling
- scanf for menu selection without & (bug: should be &n)

## Common Issues
- Inconsistent file paths: Some files reference `./data/library.dat` instead of `./data/libraryBook.dat`
- scanf bugs: Missing & in scanf calls (e.g., `scanf("%d", n)` should be `scanf("%d", &n)`)
- Logic errors: In deleteBook, `if(deleteBook.id = targetId)` should be `==`, and found flag logic incorrect

## Development Workflow
- Edit .c files in `src/`, headers in `include/`
- Compile and test manually with gcc
- Data files created automatically in `./data/` on first write
- No automated tests; manual testing via console menus
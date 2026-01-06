#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "book.h"

void displayBook()
{
    struct book displayBook;
    FILE *file = fopen("../data/libraryBook.dat", "rb");

    if(file == NULL){
        printf("Can't open the file!\n");
        return;
    }

    printf("\n%-6s | %-30s | %-20s | %-10s\n",
           "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------\n");

    while (fread(&displayBook, sizeof(struct book), 1, file) == 1)
    {
        printf("%-6d | %-30s | %-20s | %-10s\n",
               displayBook.id,
               displayBook.title,
               displayBook.author,
               displayBook.status == 0 ? "Available" : "Borrowed");
    }

    fclose(file);    
}

void displayUser()
{
    struct user u;
    struct borrow br;
    struct book b;

    FILE *userFile   = fopen("../data/libraryUser.dat", "rb");
    FILE *borrowFile = fopen("../data/borrowBook.dat", "rb");
    FILE *bookFile   = fopen("../data/libraryBook.dat", "rb");
    
    if (!userFile || !borrowFile || !bookFile)
    {
        printf("Can't open file!\n");
        if (userFile) fclose(userFile);
        if (borrowFile) fclose(borrowFile);
        if (bookFile) fclose(bookFile);
        return;
    }
    
    printf("\nUSER LIST\n");
    printf("--------------------------------------------------\n");

    while (fread(&u, sizeof(struct user), 1, userFile) == 1)
    {
        printf("\nUser ID: %d\nUser Name: %s", u.id, u.name);
        printf("Borrowed books:\n");

        //rewind dua con tro file ve dau file va xoa co EOF
        rewind(borrowFile); // = fseek(file, 0, SEEK_SET); clearerr(file);
        int hasBorrow = 0;

        while (fread(&br, sizeof(struct borrow), 1, borrowFile) == 1)
        {
            if (br.userId == u.id)
            {
                rewind(bookFile);

                while (fread(&b, sizeof(struct book), 1, bookFile) == 1)
                {
                    if (b.id == br.bookId)
                    {
                        printf("  - %s (%s)\n",
                               b.title,
                               b.author);
                        hasBorrow = 1;
                        break;
                    }
                }
            }
        }

        if (!hasBorrow)
            printf("  No borrowed books\n");
    }

    fclose(userFile);
    fclose(borrowFile);
    fclose(bookFile);
}

void lookupTitle(char targetTitle[100])
{
    struct book b;

    FILE *book = fopen("../data/libraryBook.dat", "rb");
    if(!book)
    {
        printf("Can't open the file!");
        return;
    }

    printf("\n%-6s | %-30s | %-20s | %-10s\n",
        "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------\n");

    while(fread(&b, sizeof(struct book), 1, book))
    {
        if(strcmp(b.title, targetTitle) == 0)
        {
            printf("%-6d | %-30s | %-20s | %-10s\n",
                b.id,
                b.title,
                b.author,
                b.status == 0 ? "Available" : "Borrowed");            
        }
    }

    fclose(book);
}

void lookupAuthor(char targetAuthor[50])
{
    struct book b;

    FILE *book = fopen("../data/libraryBook.dat", "rb");
    if(!book)
    {
        printf("Can't open the file!");
        return;
    }

    printf("\n%-6s | %-30s | %-20s | %-10s\n",
        "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------\n");

    while(fread(&b, sizeof(struct book), 1, book))
    {
        if(strcmp(b.author, targetAuthor))
        {
            printf("%-6d | %-30s | %-20s | %-10s\n",
                b.id,
                b.title,
                b.author,
                b.status == 0 ? "Available" : "Borrowed");            
        }
    }

    fclose(book);
}
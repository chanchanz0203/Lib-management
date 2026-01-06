#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "book.h"

void borrowBook(int IdUser, int IdBook)
{
    struct user u;
    struct borrow br;
    struct book b;

    FILE *userFile   = fopen("../data/libraryUser.dat", "rb");
    FILE *borrowFile = fopen("../data/borrowBook.dat", "ab");
    FILE *bookFile   = fopen("../data/libraryBook.dat", "rb+");
    
    if (!userFile || !borrowFile || !bookFile)
    {
        printf("Can't open file!\n");
        if (userFile) fclose(userFile);
        if (borrowFile) fclose(borrowFile);
        if (bookFile) fclose(bookFile);
        return;
    }

    int foundUser = 0;
    int foundBook = 0;

    while (fread(&u, sizeof(struct user),1, userFile) == 1)
    {
        if(u.id == IdUser)
        {
            foundUser = 1;
            break;
        }
    }

    if(foundUser == 0)
    {
        printf("This user doesn't exit!\n");
    }

    rewind(bookFile);

    while (foundUser && fread(&b, sizeof(struct book), 1, bookFile))
    {
        if(b.id == IdBook)
        {
            foundBook = 1;

            if(b.status == 1)
            {
                printf("This book is borrowed!\n");
                break;
            }else
            {
                b.status = 1;
                fseek(bookFile, -(long)sizeof(struct book), SEEK_CUR);
                fwrite(&b, sizeof(struct book), 1, bookFile);
                fflush(bookFile);

                br.userId = IdUser;
                br.bookId = IdBook;
                fwrite(&br, sizeof(struct borrow), 1, borrowFile);
                fflush(borrowFile);
                printf("You borrow successful!\n");
                break;
            }
        }
    }

    if(foundUser && !foundBook)
    {
        printf("This book doesn't exit!\n");
    }

    fclose(userFile);
    fclose(bookFile);
    fclose(borrowFile);
}

void returnBook(int IdUser, int IdBook)
{
    struct borrow br;
    struct book b;

    FILE *userFile   = fopen("../data/libraryUser.dat", "rb");
    FILE *borrowFile = fopen("../data/borrowBook.dat", "rb");
    FILE *bookFile   = fopen("../data/libraryBook.dat", "rb+");
    FILE *tempBorrowFile= fopen("../data/tempborrow.dat", "wb"); 
    
    if (!userFile || !borrowFile || !bookFile || !tempBorrowFile)
    {
        printf("Can't open file!\n");
        if (userFile) fclose(userFile);
        if (borrowFile) fclose(borrowFile);
        if (bookFile) fclose(bookFile);
        if (tempBorrowFile) fclose(tempBorrowFile);
        return;
    }    

    int found = 0;

    while(fread(&br, sizeof(struct borrow), 1, borrowFile) == 1)
    {
        if((br.bookId == IdBook) && (br.userId == IdUser))
        {
            found = 1;
            continue;
        }

        //sao chep du lieu vao file temp
        fwrite(&br, sizeof( struct borrow), 1, tempBorrowFile);
    }

    rewind(bookFile);
    while(found && fread(&b, sizeof(struct book), 1, bookFile))
    {
        if(b.id == IdBook)
        {
            b.status = 0;
            fseek(bookFile, -(long)sizeof(struct book), SEEK_CUR);
            fwrite(&b, sizeof(struct book), 1, bookFile);
            break;
        }
    }

    fclose(userFile);
    fclose(bookFile);
    fclose(borrowFile);
    fclose(tempBorrowFile);

    remove("../data/borrowBook.dat");
    rename("../data/tempborrow.dat", "../data/borrowBook.dat");

    if(found)
    {
        printf("Return successfuly!\n");
    }else
    {
        printf("Wrong information!\n");
    }
}
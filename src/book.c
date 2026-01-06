#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void addBook()
{
    struct book newBook;
    FILE *file = fopen("../data/libraryBook.dat","ab"); //"ab" ghi them

    if(file == NULL)
    {
        printf("Can't open the file!\n");
        return;
    }

    printf("Enter Book ID: ");
    if(scanf("%d", &newBook.id) != 1)
    {
        printf("Invalid input!\n");
        return;
    }
    getchar(); //clear input buffer

    printf("Enter Book Title: ");
    fgets(newBook.title, 100, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; //strcspn for find and remove unwanted characters


    printf("Enter Book Author: ");
    fgets(newBook.author, 50, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';   

    newBook.status = 0;

    if (fwrite(&newBook, sizeof(struct book), 1, file) != 1)
    {
        printf("Write file failed!\n");
    }
    else
    {
        printf("Book added successfully!\n");
    }

    fclose(file);
}

void editBook(int targetId)
{
    char buffer[100];
    struct book editBook;
    FILE *file = fopen("../data/libraryBook.dat","rb+"); //rb+ doc va ghi

    if(file == NULL)
    {
        printf("Can't open the file!\n");
        return;
    }

    while(fread(&editBook, sizeof(struct book),1, file) == 1)
    {
        if(editBook.id == targetId)
        {
            printf("Edit Book Title\nIf Book Title Doesn't Change, Enter 0\n");
            printf("Enter New Book Title: \n");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if(strcmp(buffer, "0") != 0) //strcmp so sanh chuoi
            {
                strcpy(editBook.title, buffer); //strcpy sao chep chuoi
            }

            printf("Edit Book Author\nIf Book Author Doesn't Change, Enter 0\n");
            printf("Enter New Book Author: \n");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if(strcmp(buffer, "0") != 0) 
            {
                strcpy(editBook.author, buffer);
            }
            
            fseek(file, -(long)sizeof(struct book), SEEK_CUR);
            fwrite(&editBook, sizeof(struct book), 1, file);

            printf("Update successful!\n");
            break;
        }
    }
    
    fclose(file);
}

void deleteBook(int targetId)
{
    struct book deleteBook;
    FILE *file = fopen("../data/libraryBook.dat", "rb"); //rb doc file
    FILE *temp = fopen("../data/tempBook.dat", "wb"); //wb dung de xoa du lieu cua toan bo file

    if (file == NULL || temp == NULL)
    {
        printf("Can't open the file!\n\n");
        if (file) fclose(file); // neu file nao mo duoc (khac NULL) thi can dong lai (close)
        if (temp) fclose(temp);
        return;
    }
    int found = 0;

    while(fread(&deleteBook, sizeof(struct book), 1, file) == 1)
    {
        if(deleteBook.id == targetId)
        {
            found = 1;
            continue;
        }

        //sao chep du lieu vao file temp.dat
        fwrite(&deleteBook, sizeof( struct book), 1, temp);
        
    }

    fclose(file);
    fclose(temp);

    remove("../data/libraryBook.dat");
    rename("../data/tempBook.dat", "../data/libraryBook.dat");

    if(found)
    {
        printf("Book deleted successfuly!\n");
    }else
    {
        printf("Book not found!\n");
    }
}
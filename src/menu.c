#include <stdio.h>
#include "book.h"
#include "user.h"
#include "borrow_return.h"
#include "lookup_display.h"


void select1()
{
    int n;
    int targetId;

    printf("Select: \n");
    printf("1. Add Book\n");
    printf("2. Edit Book\n");
    printf("3. Delete Book\n");
    printf("4. Exit\n");
    scanf("%d", &n);

    switch(n)
    {
        case 1:
            addBook();
            break;

        case 2:
            printf("The ID of the book you want to edit.\n");
            printf("ID Book: \n");
            scanf("%d", &targetId);

            editBook(targetId);
            select1();
            break;

        case 3:
            printf("The ID of the book you want to delete.\n");
            printf("ID Book: \n");
            scanf("%d", &targetId);

            deleteBook(targetId);
            select1();
            break;

        case 4:
            break;

        default:
            printf("error");
    }
}

void select2()
{
    int n;
    int targetId;

    printf("Select: \n");
    printf("1. Add User\n");
    printf("2. Edit User\n");
    printf("3. Delete User\n");
    printf("4. Exit\n");
    scanf("%d", &n);

    switch(n)
    {
        case 1:
            addUser();
            select2();
            break;

        case 2:
            printf("The ID of the user you want to edit.\n");
            printf("ID User: \n");
            scanf("%d", &targetId);

            editUser(targetId);
            select2();
            break;

        case 3:
            printf("The ID of the user you want to delete.\n");
            printf("ID User: \n");
            scanf("%d", &targetId);

            deleteUser(targetId);
            select2();
            break;

        case 4:
            break;

        default:
            printf("error");
    }
}

void select3()
{
    int IdUser;
    int IdBook;
    int n;
    
    printf("Select: \n");
    printf("1. Borrow Book\n");
    printf("2. Return Book\n");
    printf("3. Exit\n");
    scanf("%d", &n);

    switch(n)
    {
        case 1:
            printf("Enter Your ID: \n");
            scanf("%d", &IdUser);
            printf("Enter your Book's ID: \n");
            scanf("%d", &IdBook);  
            borrowBook(IdUser, IdBook);
            select3();
            break;

        case 2:
            printf("Enter Your ID: \n");
            scanf("%d", &IdUser);
            printf("Enter your Book's ID: \n");
            scanf("%d", &IdBook);  
            returnBook(IdUser, IdBook);
            select3();
            break;

        case 3:
            break;

        default:
            printf("error");
    }
}

void select4()
{
    int n;
    char targetTitle[100];
    char targetAuthor[100];

    printf("Select: \n");
    printf("1. Display Book\n");
    printf("2. Display User\n");
    printf("3. Look up by Title\n");
    printf("4. Look up by Author\n");
    printf("5. Exit\n");
    scanf("%d", &n);

    switch(n)
    {
        case 1:
            displayBook();
            select4();
            break;

        case 2:
            displayUser();
            select4();
            break;

        case 3:
            getchar();
            printf("Enter the title book: \n");
            fgets(targetTitle, 100, stdin);
            lookupTitle(targetTitle);
            select4();
            break;

        case 4:
            getchar();
            printf("Enter the author: \n");
            fgets(targetAuthor, 100, stdin);
            lookupAuthor(targetAuthor);
            select4();
            break;

        case 5:
            break;

        default:
            printf("error");
    }
}


int menu()
{
    int n;
    printf("Select: \n");
    printf("1. Book management\n");
    printf("2. User management\n");
    printf("3. Borrow and Return Book\n");
    printf("4.Look up and Display\n");
    printf("5.Exit\n");

    scanf("%d", &n);

    switch(n)
    {
        case 1:
            select1();
            return menu();
            break;

        case 2:
            select2();
            return menu();
            break;

        case 3:
            select3();
            return menu();
            break;

        case 4:
            select4();
            return menu();
            break;
            
        case 5:
            return 0;

        default:
            printf("error");
            return menu();
    }
}
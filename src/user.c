#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "book.h"

void addUser()
{
    struct user newUser;
    FILE *file = fopen("../data/libraryUser.dat","ab"); //"ab" ghi them

    if(file == NULL)
    {
        printf("Can't open the file!\n");
        return;
    }

    printf("Enter User ID: ");
    if(scanf("%d", &newUser.id) != 1)
    {
        printf("Invalid input!\n");
        return;
    }
    getchar(); //clear input buffer

    printf("Enter User Name: ");
    fgets(newUser.name, 100, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0'; //strcspn for find and remove unwanted characters

    if (fwrite(&newUser, sizeof(struct user), 1, file) != 1)
    {
        printf("Username added failed!\n");
    }
    else
    {
        printf("User added successfully!\n");
    }

    fclose(file);
}

void editUser(int targetId)
{
    char buffer[100];
    struct user editUser;
    FILE *file = fopen("../data/libraryUser.dat","rb+"); //rb+ doc va ghi

    if(file == NULL)
    {
        printf("Can't open the file!\n");
        return;
    }

    while(fread(&editUser, sizeof(struct user),1, file) == 1)
    {
        if(editUser.id == targetId)
        {
            printf("Edit User Name\nIf User Name Doesn't Change, Enter 0\n");
            printf("Enter New User Name: \n");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if(strcmp(buffer, "0") != 0) //strcmp so sanh chuoi
            {
                strcpy(editUser.name, buffer); //strcpy sao chep chuoi
            }
            
            fseek(file, -(long)sizeof(struct user), SEEK_CUR);
            fwrite(&editUser, sizeof(struct user), 1, file);

            printf("Update successful!\n");
            break;
        }
    }
    
    fclose(file);
}

void deleteUser(int targetId)
{
    struct user deleteUser;
    FILE *file = fopen("../data/libraryUser.dat", "rb"); //rb doc file
    FILE *temp = fopen("../data/tempUser.dat", "wb"); //wb dung de xoa du lieu cua toan bo file

    if (file == NULL || temp == NULL)
    {
        printf("Can't open the file!\n");
        if (file) fclose(file); // neu file nao mo duoc (khac NULL) thi can dong lai (close)
        if (temp) fclose(temp);
        return;
    }

            int found = 0;

    while(fread(&deleteUser, sizeof(struct user), 1, file) == 1)
    {
        if(deleteUser.id == targetId)
        {
            found = 1;
            continue;
        }

        //sao chep du lieu vao file temp.dat
        fwrite(&deleteUser, sizeof( struct user), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove("../data/libraryUser.dat");
    rename("../data/tempUser.dat", "../data/libraryUser.dat");

    if(found)
    {
        printf("User deleted successfuly!\n");
    }else
    {
        printf("User not found!\n");
    }
}
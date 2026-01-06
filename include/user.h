#ifndef USER_H
#define USER_H

struct borrow
{
    int userId;
    int bookId;
};

struct user
{
    int id;
    char name[50];
};

void addUser();
void editUser(int targetId);
void deleteUser(int targetId);
void displayUser();

#endif
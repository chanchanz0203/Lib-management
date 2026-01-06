#ifndef BOOK_H
#define BOOK_H


struct book
{
    int id;
    char title[100];
    char author[50];
    int status; //0 for available, 1 for borrowed
};

void addBook();
void editBook(int targetID);
void deleteBook(int targetID);
void displayBook();

#endif
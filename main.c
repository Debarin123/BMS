#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
struct Book {
    int bookID;
    char bookName[100];
    char isbn[20];
};

// Function to add a book to the file
void addBookToFile(struct Book book) {
    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }
    fprintf(file, "%d %s %s\n", book.bookID, book.bookName, book.isbn);
    fclose(file);
}

// Function to list all books from the file
void listAllBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("No books found\n");
        return;
    }
    struct Book book;
    while (fscanf(file, "%d %s %s\n", &book.bookID, book.bookName, book.isbn) != EOF) {
        printf("BookID: %d, BookName: %s, ISBN: %s\n", book.bookID, book.bookName, book.isbn);
    }
    fclose(file);
}

// Function to delete a book from the file
void deleteBook(int bookID) {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temp file for writing\n");
        fclose(file);
        return;
    }
    struct Book book;
    int found = 0;
    while (fscanf(file, "%d %s %s\n", &book.bookID, book.bookName, book.isbn) != EOF) {
        if (book.bookID != bookID) {
            fprintf(tempFile, "%d %s %s\n", book.bookID, book.bookName, book.isbn);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);
    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("Book with ID %d deleted\n", bookID);
    } else {
        remove("temp.txt");
        printf("Book with ID %d not found\n", bookID);
    }
}

// Function to update book details
void updateBook(int bookID, char *newBookName, char *newISBN) {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temp file for writing\n");
        fclose(file);
        return;
    }
    struct Book book;
    int found = 0;
    while (fscanf(file, "%d %s %s\n", &book.bookID, book.bookName, book.isbn) != EOF) {
        if (book.bookID == bookID) {
            found = 1;
            if (newBookName != NULL) strcpy(book.bookName, newBookName);
            if (newISBN != NULL) strcpy(book.isbn, newISBN);
        }
        fprintf(tempFile, "%d %s %s\n", book.bookID, book.bookName, book.isbn);
    }
    fclose(file);
    fclose(tempFile);
    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("Book with ID %d updated\n", bookID);
    } else {
        remove("temp.txt");
        printf("Book with ID %d not found\n", bookID);
    }
}

int main() {
    int choice, bookID;
    struct Book book;
    char newBookName[100], newISBN[20];

    while (1) {
        printf("\n=========================================\n");
        printf("        Book Management System\n");
        printf("=========================================\n");
        printf("1. Add a book\n");
        printf("2. List all books\n");
        printf("3. Delete a book\n");
        printf("4. Update a book\n");
        printf("5. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter BookID: ");
                scanf("%d", &book.bookID);
                printf("Enter Book Name: ");
                scanf("%s", book.bookName);
                printf("Enter ISBN: ");
                scanf("%s", book.isbn);
                addBookToFile(book);
                printf("Book added successfully\n");
                break;
            case 2:
                printf("List of all books:\n");
                listAllBooks();
                break;
            case 3:
                printf("Enter BookID to delete: ");
                scanf("%d", &bookID);
                deleteBook(bookID);
                break;
            case 4:
                printf("Enter BookID to update: ");
                scanf("%d", &bookID);
                printf("Enter new Book Name (or 'none' to keep the same): ");
                scanf("%s", newBookName);
                printf("Enter new ISBN (or 'none' to keep the same): ");
                scanf("%s", newISBN);
                updateBook(bookID, (strcmp(newBookName, "none") != 0) ? newBookName : NULL,
                           (strcmp(newISBN, "none") != 0) ? newISBN : NULL);
                break;
            case 5:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// ---------------- STRUCTURES ----------------
typedef struct {
    int id;
    char title[50];
    char author[50];
    int quantity;
} Book;

typedef struct {
    int issueId;
    int bookId;
    int userId;
    char userName[50];
    char issueDate[20];
    char dueDate[20];
    char returnDate[20];
    int returned; // 0 = not returned, 1 = returned
} Issue;

// ---------------- GLOBAL ----------------
Book books[MAX];
Issue issues[MAX];
int bookCount = 0, issueCount = 0;

// ---------------- DATE FUNCTION ----------------
void getDate(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// ---------------- FILE HANDLING ----------------
void loadBooks() {
    FILE *fp = fopen("books.txt", "rb");
    if (fp != NULL) {
        fread(&bookCount, sizeof(int), 1, fp);
        fread(books, sizeof(Book), bookCount, fp);
        fclose(fp);
    }
}

void saveBooks() {
    FILE *fp = fopen("books.txt", "wb");
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void loadIssues() {
    FILE *fp = fopen("issues.txt", "rb");
    if (fp != NULL) {
        fread(&issueCount, sizeof(int), 1, fp);
        fread(issues, sizeof(Issue), issueCount, fp);
        fclose(fp);
    }
}

void saveIssues() {
    FILE *fp = fopen("issues.txt", "wb");
    fwrite(&issueCount, sizeof(int), 1, fp);
    fwrite(issues, sizeof(Issue), issueCount, fp);
    fclose(fp);
}

// ---------------- BOOK FUNCTIONS ----------------
void addBook() {
    printf("\nEnter Book ID: ");
    scanf("%d", &books[bookCount].id);

    printf("Enter Title: ");
    scanf(" %[^\n]", books[bookCount].title);

    printf("Enter Author: ");
    scanf(" %[^\n]", books[bookCount].author);

    printf("Enter Quantity: ");
    scanf("%d", &books[bookCount].quantity);

    bookCount++;
    printf("Book Added Successfully!\n");
}

void viewBooks() {
    printf("\n--- Book List ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d | %s | %s | Qty: %d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].quantity);
    }
}

int findBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

void removeBook() {
    int id;
    printf("Enter Book ID to remove: ");
    scanf("%d", &id);

    int index = findBookById(id);

    if (index == -1) {
        printf("Book not found!\n");
        return;
    }

    for (int i = index; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }

    bookCount--;
    printf("Book Removed!\n");
}

void searchBook() {
    char name[50];
    printf("Enter Book Name: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, name)) {
            printf("%d | %s | %s | Qty: %d\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].quantity);
        }
    }
}

// ---------------- ISSUE BOOK ----------------
void issueBook() {
    int id, userId;
    char userName[50];

    printf("Enter Book ID: ");
    scanf("%d", &id);

    int index = findBookById(id);

    if (index == -1 || books[index].quantity <= 0) {
        printf("Book not available!\n");
        return;
    }

    printf("Enter User ID: ");
    scanf("%d", &userId);

    printf("Enter User Name: ");
    scanf(" %[^\n]", userName);

    issues[issueCount].issueId = issueCount + 1;
    issues[issueCount].bookId = id;
    issues[issueCount].userId = userId;
    strcpy(issues[issueCount].userName, userName);

    getDate(issues[issueCount].issueDate);
    strcpy(issues[issueCount].dueDate, "7 days"); // simple

    strcpy(issues[issueCount].returnDate, "Not Returned");
    issues[issueCount].returned = 0;

    books[index].quantity--;
    issueCount++;

    printf("Book Issued!\n");
}

// ---------------- RETURN BOOK ----------------
void returnBook() {
    int id, userId;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    printf("Enter User ID: ");
    scanf("%d", &userId);

    for (int i = 0; i < issueCount; i++) {
        if (issues[i].bookId == id &&
            issues[i].userId == userId &&
            issues[i].returned == 0) {

            getDate(issues[i].returnDate);
            issues[i].returned = 1;

            int index = findBookById(id);
            books[index].quantity++;

            printf("Book Returned!\n");
            return;
        }
    }

    printf("Record not found!\n");
}

// ---------------- LIST ISSUED ----------------
void listIssued() {
    printf("\n--- Issued Books ---\n");
    for (int i = 0; i < issueCount; i++) {
        printf("BookID: %d | User: %s | Issue: %s | Return: %s\n",
               issues[i].bookId,
               issues[i].userName,
               issues[i].issueDate,
               issues[i].returnDate);
    }
}

// ---------------- MAIN MENU ----------------
int main() {
    int choice;

    loadBooks();
    loadIssues();

    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Remove Book\n");
        printf("4. Search Book\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. List Issued Books\n");
        printf("8. Save\n");
        printf("9. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: removeBook(); break;
            case 4: searchBook(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: listIssued(); break;
            case 8:
                saveBooks();
                saveIssues();
                printf("Data Saved!\n");
                break;
            case 9:
                saveBooks();
                saveIssues();
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
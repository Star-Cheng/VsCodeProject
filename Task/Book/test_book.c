#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 1000
#define MAX_USERS 100
#define MAX_BORROW 10

typedef struct
{
    int id;
    char title[100];
    char author[100];
    char publisher[100];
    int available;   // 0 for available, 1 for borrowed
    int borrowCount; // Number of times the book has been borrowed
} Book;

typedef struct
{
    int id;
    char name[100];
    char type[20]; // "student" or "teacher"
    int borrowedBooks[MAX_BORROW];
    int borrowCount;
} User;

typedef struct
{
    int userId;
    int bookId;
    time_t borrowDate;
    time_t returnDate;
} BorrowRecord;

Book books[MAX_BOOKS];
User users[MAX_USERS];
BorrowRecord borrowRecords[MAX_BOOKS];
int bookCount = 0;
int userCount = 0;
int borrowRecordCount = 0;

void mainMenu();
void manageBooks();
void queryBooks();
void borrowBook();
void returnBook();
void popularBooks();
void addBook();
void modifyBook();
void deleteBook();
void queryByTitle();
void queryByAuthor();
void queryByPublisher();
void listTopBooks(int period);
void manageBooks()
{
    int choice;
    printf("1   录入图书\n");
    printf("2   修改图书\n");
    printf("3   删除图书\n");
    printf("4   返回主菜单\n");
    printf("请选择[1/2/3/4]：");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addBook();
        break;
    case 2:
        modifyBook();
        break;
    case 3:
        deleteBook();
        break;
    case 4:
        return;
    default:
        printf("无效选择，请重试。\n");
    }
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("图书库已满，无法录入更多图书。\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;
    printf("输入图书标题：");
    scanf("%s", newBook.title);
    printf("输入图书作者：");
    scanf("%s", newBook.author);
    printf("输入图书出版社：");
    scanf("%s", newBook.publisher);
    newBook.available = 0;
    newBook.borrowCount = 0;

    books[bookCount] = newBook;
    bookCount++;

    printf("图书录入成功。\n");
}

void modifyBook()
{
    int id;
    printf("输入要修改的图书ID：");
    scanf("%d", &id);

    if (id <= 0 || id > bookCount)
    {
        printf("无效的图书ID。\n");
        return;
    }

    Book *book = &books[id - 1];
    printf("输入新的图书标题：");
    scanf("%s", book->title);
    printf("输入新的图书作者：");
    scanf("%s", book->author);
    printf("输入新的图书出版社：");
    scanf("%s", book->publisher);

    printf("图书信息修改成功。\n");
}

void deleteBook()
{
    int id;
    printf("输入要删除的图书ID：");
    scanf("%d", &id);

    if (id <= 0 || id > bookCount)
    {
        printf("无效的图书ID。\n");
        return;
    }

    for (int i = id - 1; i < bookCount - 1; i++)
    {
        books[i] = books[i + 1];
    }
    bookCount--;

    printf("图书删除成功。\n");
}
void queryBooks()
{
    int choice;
    printf("1   按书名查询\n");
    printf("2   按作者查询\n");
    printf("3   按出版社查询\n");
    printf("4   返回主菜单\n");
    printf("请选择[1/2/3/4]：");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        queryByTitle();
        break;
    case 2:
        queryByAuthor();
        break;
    case 3:
        queryByPublisher();
        break;
    case 4:
        return;
    default:
        printf("无效选择，请重试。\n");
    }
}

void queryByTitle()
{
    char title[100];
    printf("输入书名：");
    scanf("%s", title);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            printf("ID: %d, 标题: %s, 作者: %s, 出版社: %s, 状态: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].publisher,
                   books[i].available ? "已借出" : "可借");
        }
    }
}

void queryByAuthor()
{
    char author[100];
    printf("输入作者名：");
    scanf("%s", author);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].author, author) == 0)
        {
            printf("ID: %d, 标题: %s, 作者: %s, 出版社: %s, 状态: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].publisher,
                   books[i].available ? "已借出" : "可借");
        }
    }
}

void queryByPublisher()
{
    char publisher[100];
    printf("输入出版社名：");
    scanf("%s", publisher);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].publisher, publisher) == 0)
        {
            printf("ID: %d, 标题: %s, 作者: %s, 出版社: %s, 状态: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].publisher,
                   books[i].available ? "已借出" : "可借");
        }
    }
}
void borrowBook()
{
    int userId, bookId;
    printf("输入用户ID:");
    scanf("%d", &userId);
    getchar(); // 清除输入缓冲区中的换行符
    printf("输入图书ID:");
    scanf("%d", &bookId);
    getchar(); // 清除输入缓冲区中的换行符

    if (userId <= 0 || userId > userCount || bookId <= 0 || bookId > bookCount)
    {
        printf("无效的用户ID或图书ID。\n");
        return;
    }

    User *user = &users[userId - 1];
    Book *book = &books[bookId - 1];

    if (book->available)
    {
        printf("该图书已被借出。\n");
        return;
    }

    if (user->borrowCount >= MAX_BORROW)
    {
        printf("用户已达到借书上限。\n");
        return;
    }

    // 更新图书状态
    book->available = 1;

    // 更新用户借书记录
    user->borrowedBooks[user->borrowCount++] = book->id;

    // 添加借书记录
    BorrowRecord newRecord;
    newRecord.userId = user->id;
    newRecord.bookId = book->id;
    newRecord.borrowDate = time(NULL);
    newRecord.returnDate = 0;
    borrowRecords[borrowRecordCount++] = newRecord;

    printf("借书成功。\n");
}

void returnBook()
{
    int userId, bookId;
    printf("输入用户ID:");
    scanf("%d", &userId);
    printf("输入图书ID:");
    scanf("%d", &bookId);

    if (userId <= 0 || userId > userCount || bookId <= 0 || bookId > bookCount)
    {
        printf("无效的用户ID或图书ID。\n");
        return;
    }

    User *user = &users[userId - 1];
    Book *book = &books[bookId - 1];

    if (!book->available)
    {
        printf("该图书未被借出。\n");
        return;
    }

    // 更新图书状态
    book->available = 0;

    // 更新用户借书记录
    int i;
    for (i = 0; i < user->borrowCount; i++)
    {
        if (user->borrowedBooks[i] == bookId)
        {
            break;
        }
    }
    if (i == user->borrowCount)
    {
        printf("用户未借阅该图书。\n");
        return;
    }
    for (; i < user->borrowCount - 1; i++)
    {
        user->borrowedBooks[i] = user->borrowedBooks[i + 1];
    }
    user->borrowCount--;

    // 更新借书记录
    for (i = 0; i < borrowRecordCount; i++)
    {
        if (borrowRecords[i].userId == userId && borrowRecords[i].bookId == bookId && borrowRecords[i].returnDate == 0)
        {
            borrowRecords[i].returnDate = time(NULL);
            break;
        }
    }

    printf("还书成功。\n");
}

void popularBooks()
{
    int choice;
    printf("1   按月查询\n");
    printf("2   按年查询\n");
    printf("请选择[1/2]:");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        listTopBooks(30);
        break;
    case 2:
        listTopBooks(365);
        break;
    default:
        printf("无效选择，请重试。\n");
    }
}

void listTopBooks(int period)
{
    // Your implementation to list top borrowed books in the given period
}

void mainMenu()
{
    int choice;
    printf("1   图书信息管理\n");
    printf("2   图书信息查询\n");
    printf("3   借书业务\n");
    printf("4   还书业务\n");
    printf("5   热门图书\n");
    printf("6   退出系统\n");
    printf("请选择[1/2/3/4/5/6]:");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        manageBooks();
        break;
    case 2:
        queryBooks();
        break;
    case 3:
        borrowBook();
        break;
    case 4:
        returnBook();
        break;
    case 5:
        popularBooks();
        break;
    case 6:
        exit(0);
    default:
        printf("无效选择，请重试。\n");
    }
}
int main()
{
    while (1)
    {
        mainMenu();
        getchar(); // 清除输入缓冲区中的换行符
    }
    return 0;
}

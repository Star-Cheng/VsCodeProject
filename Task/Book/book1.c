#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_BORROWERS 100

struct Book {
    char title[50];
    char author[50];
    char publisher[50];
    int borrowedCount; // 借阅次数
};

struct Borrower {
    char name[50];
    int borrowedBookIndex; // -1 表示未借书
    int overdue; // 超期标志
};

struct Book books[MAX_BOOKS];
struct Borrower borrowers[MAX_BORROWERS];
int numBooks = 0;
int numBorrowers = 0;

void displayMenu() {
    printf("\n1   图书信息管理\n");
    printf("2   图书信息查询\n");
    printf("3   借书业务\n");
    printf("4   还书业务\n");
    printf("5   热门图书\n");
    printf("6   退出系统\n");
    printf("请选择[1/2/3/4/5/6]：");
}

void addBook() {
    if (numBooks < MAX_BOOKS) {
        printf("请输入书名：");
        scanf("%s", books[numBooks].title);
        printf("请输入作者：");
        scanf("%s", books[numBooks].author);
        printf("请输入出版社：");
        scanf("%s", books[numBooks].publisher);
        books[numBooks].borrowedCount = 0;
        numBooks++;
        printf("图书信息添加成功。\n");
    } else {
        printf("图书信息已满，无法添加新书。\n");
    }
}

void modifyBook() {
    char title[50];
    printf("请输入要修改的图书书名：");
    scanf("%s", title);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("请输入新的书名：");
            scanf("%s", books[i].title);
            printf("请输入新的作者：");
            scanf("%s", books[i].author);
            printf("请输入新的出版社：");
            scanf("%s", books[i].publisher);
            printf("图书信息修改成功。\n");
            return;
        }
    }
    printf("未找到该书名的图书。\n");
}

void deleteBook() {
    char title[50];
    printf("请输入要删除的图书书名：");
    scanf("%s", title);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].title, title) == 0) {
            for (int j = i; j < numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            numBooks--;
            printf("图书信息删除成功。\n");
            return;
        }
    }
    printf("未找到该书名的图书。\n");
}

void manageBooks() {
    int choice;
    printf("\n1   添加图书\n");
    printf("2   修改图书\n");
    printf("3   删除图书\n");
    printf("4   返回主菜单\n");
    printf("请选择[1/2/3/4]：");
    scanf("%d", &choice);
    
    switch (choice) {
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
            printf("无效的选项，请重新选择。\n");
    }
}

void searchBooks() {
    int choice;
    char keyword[50];
    printf("\n1   按书名查询\n");
    printf("2   按作者查询\n");
    printf("3   按出版社查询\n");
    printf("4   返回主菜单\n");
    printf("请选择[1/2/3/4]：");
    scanf("%d", &choice);
    
    printf("请输入查询关键词：");
    scanf("%s", keyword);
    
    for (int i = 0; i < numBooks; i++) {
        if ((choice == 1 && strstr(books[i].title, keyword)) ||
            (choice == 2 && strstr(books[i].author, keyword)) ||
            (choice == 3 && strstr(books[i].publisher, keyword))) {
            printf("书名：%s  作者：%s  出版社：%s  借阅次数：%d\n", books[i].title, books[i].author, books[i].publisher, books[i].borrowedCount);
        }
    }
}

void borrowBook() {
    char name[50], title[50];
    printf("请输入您的姓名：");
    scanf("%s", name);
    
    // 验证身份
    int borrowerIndex = -1;
    for (int i = 0; i < numBorrowers; i++) {
        if (strcmp(borrowers[i].name, name) == 0) {
            borrowerIndex = i;
            break;
        }
    }
    if (borrowerIndex == -1) {
        borrowerIndex = numBorrowers++;
        strcpy(borrowers[borrowerIndex].name, name);
        borrowers[borrowerIndex].borrowedBookIndex = -1;
        borrowers[borrowerIndex].overdue = 0;
    }
    
    if (borrowers[borrowerIndex].borrowedBookIndex != -1) {
        printf("您已借阅了一本书，请先归还。\n");
        return;
    }
    
    printf("请输入要借的图书书名：");
    scanf("%s", title);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].title, title) == 0) {
            borrowers[borrowerIndex].borrowedBookIndex = i;
            books[i].borrowedCount++;
            printf("借书成功。\n");
            return;
        }
    }
    printf("未找到该书名的图书。\n");
}

void returnBook() {
    char name[50];
    printf("请输入您的姓名：");
    scanf("%s", name);
    
    // 验证身份
    int borrowerIndex = -1;
    for (int i = 0; i < numBorrowers; i++) {
        if (strcmp(borrowers[i].name, name) == 0) {
            borrowerIndex = i;
            break;
        }
    }
    if (borrowerIndex == -1 || borrowers[borrowerIndex].borrowedBookIndex == -1) {
        printf("您没有借书记录。\n");
        return;
    }
    
    // 检查是否超期
    if (borrowers[borrowerIndex].overdue) {
        printf("您有超期未还的图书，请缴纳罚款。\n");
    }
    
    borrowers[borrowerIndex].borrowedBookIndex = -1;
    printf("还书成功。\n");
}

void displayTopBooks() {
    int n;
    printf("请输入要显示的排行榜数量：");
    scanf("%d", &n);
    
    struct Book sortedBooks[MAX_BOOKS];
    memcpy(sortedBooks, books, sizeof(books));
    
    // 简单选择排序
    for (int i = 0; i < numBooks - 1; i++) {
        for (int j = i + 1; j < numBooks; j++) {
            if (sortedBooks[i].borrowedCount < sortedBooks[j].borrowedCount) {
                struct Book temp = sortedBooks[i];
                sortedBooks[i] = sortedBooks[j];
                sortedBooks[j] = temp;
            }
        }
    }
    
    printf("借阅次数排名前 %d 的图书：\n", n);
    for (int i = 0; i < n && i < numBooks; i++) {
        printf("书名：%s  作者：%s  出版社：%s  借阅次数：%d\n", sortedBooks[i].title, sortedBooks[i].author, sortedBooks[i].publisher, sortedBooks[i].borrowedCount);
    }
}

int main() {
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                manageBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                displayTopBooks();
                break;
            case 6:
                printf("退出系统。\n");
                break;
            default:
                printf("无效的选项，请重新选择。\n");
        }
        
    } while (choice != 6);
    
    return 0;
}

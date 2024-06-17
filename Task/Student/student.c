#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义学生结构体
typedef struct {
    char name[50];
    char id[20];
    char hometown[50];
    char interest[50];
    char religion[20];
    char nationality[50];
    int isAbroad; // 1表示境外生
} Student;

// 定义宿舍结构体
typedef struct {
    int roomNumber;
    Student* students[4]; // 每个宿舍最多4人
    int studentCount;
} Dormitory;

// 初始化学生信息
Student* createStudent(const char* name, const char* id, const char* hometown, const char* interest, const char* religion, const char* nationality, int isAbroad) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(student->name, name);
    strcpy(student->id, id);
    strcpy(student->hometown, hometown);
    strcpy(student->interest, interest);
    strcpy(student->religion, religion);
    strcpy(student->nationality, nationality);
    student->isAbroad = isAbroad;
    return student;
}

// 初始化宿舍
Dormitory* createDormitory(int roomNumber) {
    Dormitory* dorm = (Dormitory*)malloc(sizeof(Dormitory));
    if (dorm == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    dorm->roomNumber = roomNumber;
    dorm->studentCount = 0;
    return dorm;
}

// 分配宿舍床位
void assignDormitory(Dormitory* dorm, Student* student) {
    if (dorm->studentCount < 4) {
        dorm->students[dorm->studentCount++] = student;
        printf("Assigned %s to Dormitory %d\n", student->name, dorm->roomNumber);
    } else {
        printf("Dormitory %d is full\n", dorm->roomNumber);
    }
}

// 示例代码：根据条件判断是否可以放在同一个宿舍
int canBeInSameDorm(Student* student1, Student* student2) {
    if (strcmp(student1->religion, student2->religion) == 0) {
        return 1; // 宗教相同
    }
    if (student1->isAbroad && student2->isAbroad) {
        return 1; // 境外生
    }
    if (strcmp(student1->interest, student2->interest) == 0) {
        return 1; // 兴趣相同
    }
    if (strcmp(student1->hometown, student2->hometown) != 0) {
        return 1; // 籍贯不同
    }
    return 0;
}

int main() {
    // 示例学生信息
    Student* student1 = createStudent("John", "001", "Beijing", "Reading", "Christianity", "China", 0);
    Student* student2 = createStudent("Alice", "002", "Shanghai", "Sports", "Buddhism", "China", 1);
    Student* student3 = createStudent("Bob", "003", "Guangzhou", "Music", "Islam", "China", 0);

    // 示例宿舍初始化
    Dormitory* dorm1 = createDormitory(101);
    Dormitory* dorm2 = createDormitory(102);

    // 示例分配宿舍床位
    assignDormitory(dorm1, student1);
    assignDormitory(dorm1, student2);
    assignDormitory(dorm2, student3);

    // 示例条件判断
    if (canBeInSameDorm(student1, student2)) 
    {
        printf("%s and %s can be in the same dorm\n", student1->name, student2->name);
    }

    // 释放内存
    free(student1);
    free(student2);
    free(student3);
    free(dorm1);
}

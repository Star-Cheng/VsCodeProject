#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct {
    char name[50];
    char id[20];
    char hometown[50];
    char religion[20];
    char interest[50];
    int foreign;
    int satisfaction; // 满意度
} Student;

// 宿舍结构体
typedef struct {
    int roomNumber;
    Student *students;
    int numStudents;
} Dormitory;

// 函数声明
void assignBed(Student *student, Dormitory *dorms, int numDorms);
void printDormitoryAllocation(Dormitory *dorms, int numDorms);

int main() {
    int numStudents = 10; // 假设有10个学生
    int numDorms = 5;    // 假设有5个宿舍

    Student students[] = {
        {"Alice", "S001", "Beijing", "Buddhism", "Reading", 0, 0},
        {"Bob", "S002", "Shanghai", "Christianity", "Sports", 0, 0},
        {"Charlie", "S003", "Guangzhou", "Islam", "Music", 1, 0},
        {"David", "S004", "Chengdu", "Hinduism", "Art", 0, 0},
        {"Eva", "S005", "Wuhan", "Buddhism", "Movies", 0, 0},
        {"Frank", "S006", "Beijing", "Christianity", "Sports", 0, 0},
        {"Grace", "S007", "Shanghai", "Islam", "Reading", 1, 0},
        {"Henry", "S008", "Guangzhou", "Hinduism", "Music", 0, 0},
        {"Ivy", "S009", "Chengdu", "Christianity", "Art", 0, 0},
        {"Jack", "S010", "Wuhan", "Buddhism", "Movies", 0, 0},
    };

    Dormitory dorms[] = {
        {1, NULL, 0},
        {2, NULL, 0},
        {3, NULL, 0},
        {4, NULL, 0},
        {5, NULL, 0},
    };

    // 分配床位
    for (int i = 0; i < numStudents; ++i) {
        assignBed(&students[i], dorms, numDorms);
    }

    // 打印宿舍分配情况
    printDormitoryAllocation(dorms, numDorms);

    return 0;
}

// 分配床位函数
void assignBed(Student *student, Dormitory *dorms, int numDorms) {
    int maxSatisfaction = -1;
    int selectedDorm = -1;

    for (int i = 0; i < numDorms; ++i) {
        // 检查宗教、籍贯、兴趣等条件
        int satisfyReligion = 0;
        int satisfyHometown = 0;
        int satisfyInterest = 0;

        for (int j = 0; j < dorms[i].numStudents; ++j) {
            if (strcmp(student->religion, dorms[i].students[j].religion) == 0) {
                satisfyReligion = 1;
                break;
            }
        }

        for (int j = 0; j < dorms[i].numStudents; ++j) {
            if (student->foreign == dorms[i].students[j].foreign) {
                satisfyHometown = 1;
                break;
            }
        }

        for (int j = 0; j < dorms[i].numStudents; ++j) {
            if (strcmp(student->interest, dorms[i].students[j].interest) == 0) {
                satisfyInterest = 1;
                break;
            }
        }

        // 计算满意度
        int satisfaction = satisfyReligion + satisfyHometown + satisfyInterest;

        // 选择满意度最高的宿舍
        if (satisfaction > maxSatisfaction || (satisfaction == maxSatisfaction && dorms[i].numStudents < dorms[selectedDorm].numStudents)) {
            maxSatisfaction = satisfaction;
            selectedDorm = i;
        }
    }

    // 分配床位
    dorms[selectedDorm].students = (Student *)realloc(dorms[selectedDorm].students, (dorms[selectedDorm].numStudents + 1) * sizeof(Student));
    dorms[selectedDorm].students[dorms[selectedDorm].numStudents] = *student;
    dorms[selectedDorm].numStudents++;
}

// 打印宿舍分配情况函数
void printDormitoryAllocation(Dormitory *dorms, int numDorms) {
    printf("宿舍分配情况：\n");

    for (int i = 0; i < numDorms; ++i) {
        printf("宿舍 %d:\n", dorms[i].roomNumber);
        for (int j = 0; j < dorms[i].numStudents; ++j) {
            printf("  学生姓名: %s, 学号: %s, 籍贯: %s, 宗教: %s, 兴趣: %s, 是否境外生: %s\n",
                   dorms[i].students[j].name, dorms[i].students[j].id, dorms[i].students[j].hometown,
                   dorms[i].students[j].religion, dorms[i].students[j].interest,
                   dorms[i].students[j].foreign ? "是" : "否");
        }
        printf("\n");
    }
}

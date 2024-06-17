#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_DORMS 5

typedef struct {
    char name[20];
    char id[5];
    char hometown[20];
    char religion[20];
    char interest[20];
    int foreign;
    int assigned;
} Student;

typedef struct {
    int id;
    Student *students;
    int numStudents;
} Dormitory;

int hasSameReligion(Dormitory *dorm, char *religion) {
    if (dorm->numStudents == 0) {
        return 1;  // 宿舍没有学生，宗教相同
    }
    for (int i = 0; i < dorm->numStudents; ++i) {
        if (strcmp(dorm->students[i].religion, religion) == 0) {
            return 1;  // 宗教相同
        }
    }
    return 0;  // 宗教不同
}

void assignBed(Student *student, Dormitory *dorms, int numDorms) {
    int maxSatisfaction = -1;
    int selectedDorm = -1;

    for (int i = 0; i < numDorms; ++i) {
        // 检查宗教、籍贯、兴趣等条件
        int satisfyReligion = 0;
        int satisfyHometown = 0;
        int satisfyInterest = 0;

        // 新增宗教相同的学生优先选择宿舍的逻辑
        if (!hasSameReligion(&dorms[i], student->religion)) {
            continue;  // 宗教不同，跳过该宿舍
        }
        satisfyReligion = 2;  // 宗教完全一样

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
        if (satisfaction > maxSatisfaction) {
            maxSatisfaction = satisfaction;
            selectedDorm = i;
        }
    }

    // 分配床位
    if (selectedDorm != -1) {
        if (dorms[selectedDorm].numStudents == 0) {
            dorms[selectedDorm].students = (Student *)malloc(sizeof(Student));
        } else {
            dorms[selectedDorm].students = (Student *)realloc(dorms[selectedDorm].students, 
                (dorms[selectedDorm].numStudents + 1) * sizeof(Student));
        }
        dorms[selectedDorm].students[dorms[selectedDorm].numStudents] = *student;
        dorms[selectedDorm].numStudents++;
        student->assigned = 1;
    }
}

void printDormitoryAllocation(Dormitory *dorms, int numDorms) {
    for (int i = 0; i < numDorms; ++i) {
        printf("宿舍%d分配情况：\n", dorms[i].id);
        for (int j = 0; j < dorms[i].numStudents; ++j) {
            printf("姓名：%s, 宗教：%s, 是否外国人：%s\n", dorms[i].students[j].name, dorms[i].students[j].religion, dorms[i].students[j].foreign ? "是" : "否");
        }
        printf("\n");
    }
}

int main() {
    int numStudents = MAX_STUDENTS;
    int numDorms = MAX_DORMS;

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

    // 释放内存
    for (int i = 0; i < numDorms; ++i) {
        free(dorms[i].students);
    }

    return 0;
}

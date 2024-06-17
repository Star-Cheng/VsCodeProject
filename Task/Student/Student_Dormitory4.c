#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DORMITORY_COUNT 5
#define STUDENT_COUNT 20

// 学生结构体
typedef struct {
    char name[20]; // 姓名
    int id; // 学号
    char hometown[20]; // 籍贯
    char hobby[20]; // 兴趣爱好
    char ethnicity[20]; // 民族
    char religion[20]; // 宗教信仰
    bool is_foreign; // 是否境外生
} Student;

// 宿舍结构体
typedef struct {
    Student students[4]; // 学生数组
    int capacity; // 宿舍容量
} Dormitory;

// 初始化宿舍
void initializeDormitories(Dormitory dormitories[], int count) {
    for (int i = 0; i < count; i++) {
        dormitories[i].capacity = 4;
    }
}

// 计算两个学生之间的相似度
double calculateSimilarity(Student s1, Student s2) {
    double similarity = 0;

    // 宗教相同
    if (strcmp(s1.religion, s2.religion) == 0) {
        similarity += 2;
    }

    // 境外生
    if (s1.is_foreign && s2.is_foreign) {
        similarity += 1;
    }

    // 兴趣相同
    if (strcmp(s1.hobby, s2.hobby) == 0) {
        similarity += 1.5;
    }

    // 籍贯不同
    if (strcmp(s1.hometown, s2.hometown) != 0) {
        similarity += 1;
    }

    return similarity;
}

// 分配学生到宿舍
void assignStudentToDorm(Student student, Dormitory dormitories[], int count) {
    double maxSimilarity = 0;
    int bestDormitory = -1;

    // 找到最相似的宿舍
    for (int i = 0; i < count; i++) {
        if (dormitories[i].capacity > 0) {
            for (int j = 0; j < dormitories[i].capacity; j++) {
                double similarity = calculateSimilarity(student, dormitories[i].students[j]);
                if (similarity > maxSimilarity) {
                    maxSimilarity = similarity;
                    bestDormitory = i;
                }
            }
        }
    }

    if (bestDormitory != -1) {
        int index = dormitories[bestDormitory].capacity - 1;
        dormitories[bestDormitory].students[index] = student;
        dormitories[bestDormitory].capacity--;
        printf("%s 分配到宿舍 %d\n", student.name, bestDormitory + 1);
    } else {
        printf("没有可用宿舍: %s\n", student.name);
    }
}

// 打印宿舍分配情况
void printDormitoryList(Dormitory dormitories[], int count) {
    printf("Dormitory List:\n");
    for (int i = 0; i < count; i++) {
        printf("Dormitory %d: ", i + 1);
        if (dormitories[i].capacity == 4) {
            printf("Empty\n");
        } else {
            for (int j = 0; j < 4 - dormitories[i].capacity; j++) {
                printf("%s ", dormitories[i].students[j].name);
            }
            printf("\n");
        }
    }
}

// 基于协同过滤的加权分配算法
void assignStudentToDormWithCF(Student student, Dormitory dormitories[], int count) {
    double maxSimilarity = 0;
    int bestDormitory = -1;

    // 找到最相似的宿舍
    for (int i = 0; i < count; i++) {
        if (dormitories[i].capacity > 0) {
            double similarity_sum = 0;
            double weight_sum = 0;
            for (int j = 0; j < dormitories[i].capacity; j++) {
                double similarity = calculateSimilarity(student, dormitories[i].students[j]);
                double weight = 1 / (1 + similarity);
                similarity_sum += similarity * weight;
                weight_sum += weight;
            }
            double avg_similarity = similarity_sum / weight_sum;
            if (avg_similarity > maxSimilarity) {
                maxSimilarity = avg_similarity;
                bestDormitory = i;
            }
        }
    }

    if (bestDormitory != -1) {
        int index = dormitories[bestDormitory].capacity - 1;
        dormitories[bestDormitory].students[index] = student;
        dormitories[bestDormitory].capacity--;
        printf("%s assigned to dormitory %d\n", student.name, bestDormitory + 1);
    } else {
        printf("No available dormitory for %s\n", student.name);
    }
}
// Gym
typedef struct {
    char name[20];
    char id[5];
    char hometown[20];
    char hobby[20];
    char ethnicity[20];
    char religion[20];
    char hasReported[6];  // Assuming "true" or "false"
} readStudent;

int readStudentsFromFile(readStudent students[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %s %s %s %s %s %s",
                  students[count].name,
                  students[count].id,
                  students[count].hometown,
                  students[count].hobby,
                  students[count].ethnicity,
                  students[count].religion,
                  students[count].hasReported) == 7) {
        count++;
        if (count >= 100) {
            break;
        }
    }

    fclose(file);
    return count;
}

void printStudents(readStudent students[], int count) {
    printf("读取到的学生数据：\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s %s %s %s %s %s\n",
               students[i].name,
               students[i].id,
               students[i].hometown,
               students[i].hobby,
               students[i].ethnicity,
               students[i].religion,
               students[i].hasReported);
    }
}


// Gym

int main() {
    Dormitory dormitories[DORMITORY_COUNT];
    initializeDormitories(dormitories, DORMITORY_COUNT);

    // 读取学生信息
    Student students[STUDENT_COUNT];
    int studentCount = readStudentsFromFile(students, "student_en.txt");

    if (studentCount <= 0) {
        printf("未读取到学生数据。\n");
        return 1;
    }

    // 分配宿舍
    for (int i = 0; i < studentCount; i++) {
        assignStudentToDorm(students[i], dormitories, DORMITORY_COUNT);
    }

    // 打印宿舍分配情况
    printDormitoryList(dormitories, DORMITORY_COUNT);

    return 0;
}

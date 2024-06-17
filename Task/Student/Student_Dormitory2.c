#include <stdio.h>
#include <string.h>

#define DORMITORY_COUNT 10
#define STUDENT_COUNT 14

typedef struct {
    char name[20];
    int id;
    char hometown[20];
    char hobby[20];
    char ethnicity[20];
    char religion[20];
} Student;

typedef struct {
    int id;
    int capacity;
    Student students[4]; // 假设每个宿舍最多容纳4个学生
} Dormitory;

void initializeDormitories(Dormitory dormitories[], int count) {
    for (int i = 0; i < count; i++) {
        dormitories[i].id = i + 1; // 宿舍编号从1开始
        dormitories[i].capacity = 4; // 每个宿舍最多容纳4个学生
    }
}

void assignStudentToDorm(Student student, Dormitory dormitories[], int count) {
    for (int i = 0; i < count; i++) {
        Dormitory *dorm = &dormitories[i];
        if (dorm->capacity > 0) {
            int canBeAssigned = 0; // 用于标记学生是否可以被分配到该宿舍
            for (int j = 0; j < 4; j++) {
                if (strlen(dorm->students[j].name) == 0 || 
                    strcmp(dorm->students[j].religion, student.religion) == 0) {
                    // 学生可以被分配到该宿舍
                    canBeAssigned = 1;
                    strcpy(dorm->students[j].name, student.name);
                    strcpy(dorm->students[j].religion, student.religion);
                    dorm->capacity--;
                    break;
                } else if (strcmp(dorm->students[j].hobby, student.hobby) == 0) {
                    // 学生的兴趣爱好与宿舍中已有学生的兴趣爱好相同
                    canBeAssigned = 1;
                    strcpy(dorm->students[j].name, student.name);
                    strcpy(dorm->students[j].religion, student.religion);
                    dorm->capacity--;
                    break;
                } else if (strcmp(dorm->students[j].hometown, student.hometown) == 0) {
                    // 学生的籍贯与宿舍中已有学生的籍贯相同
                    canBeAssigned = 1;
                    strcpy(dorm->students[j].name, student.name);
                    strcpy(dorm->students[j].religion, student.religion);
                    dorm->capacity--;
                    break;
                }
            }
            if (canBeAssigned) {
                printf("学生 %s 被分配到宿舍 %d\n", student.name, dorm->id);
                return;
            }
        }
    }
    printf("没有符合条件的宿舍可以分配给学生 %s\n", student.name);
}


int main() {
    // 初始化宿舍
    Dormitory dormitories[10]; // 假设有10个宿舍
    initializeDormitories(dormitories, 10);

    // 添加学生信息
    Student students[] = {
        {"ming", 1001, "北京", "篮球", "汉族", "佛教"},
        {"li", 1002, "上海", "音乐", "回族", "伊斯兰教"},
        {"wamg", 1003, "广州", "电影", "汉族", "佛教"},
        {"zhao", 1004, "成都", "足球", "汉族", "基督教"},
        {"qian", 1005, "重庆", "阅读", "汉族", "佛教"},
        {"sun", 1006, "天津", "旅游", "回族", "伊斯兰教"},
        {"zhou", 1007, "南京", "编程", "汉族", "基督教"},
        {"wu", 1008, "武汉", "摄影", "汉族", "佛教"},
        {"zheng", 1009, "西安", "美术", "回族", "伊斯兰教"},
        {"geng", 1010, "杭州", "写作", "汉族", "基督教"},
        {"qing", 1011, "青岛", "游戏", "汉族", "佛教"},
        {"peng", 1012, "苏州", "舞蹈", "回族", "伊斯兰教"},
        {"cheng", 1013, "沈阳", "历史", "汉族", "基督教"},
        {"dong", 1014, "大连", "化学", "汉族", "佛教"},
        
        // 其他学生信息...
    };

    // 分配宿舍
    for (int i = 0; i < sizeof(students) / sizeof(students[0]); i++) {
        assignStudentToDorm(students[i], dormitories, 10); // 假设有10个宿舍
    }

    return 0;
}

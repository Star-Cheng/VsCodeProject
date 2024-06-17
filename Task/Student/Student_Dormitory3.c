#include <stdio.h>
#include <string.h>

// 定义学生结构体
typedef struct {
    char name[50]; // 姓名
    int id;        // 学号
    char hometown[50];  // 籍贯
    char interest[100];  // 兴趣爱好
    char ethnicity[20];  // 名族
    char religion[20];   // 宗教
} Student;

// 定义宿舍结构体
typedef struct {
    int dorm_number;
    Student students[4]; // 每个宿舍最多容纳4名学生
    int student_count;
} Dormitory;

// 初始化宿舍信息
void initializeDormitories(Dormitory dormitories[], int count) {
    for (int i = 0; i < count; i++) {
        dormitories[i].dorm_number = i + 1;
        dormitories[i].student_count = 0;
    }
}

// 将学生分配到宿舍
void assignStudentToDorm(Student student, Dormitory dormitories[], int dorm_count) {
    for (int i = 0; i < dorm_count; i++) {
        if (dormitories[i].student_count < 4) { // 宿舍还有空床位
            // 检查是否符合分配条件（宗教、兴趣、籍贯）
            // 如果符合条件，则将学生分配到该宿舍
            dormitories[i].students[dormitories[i].student_count] = student;
            dormitories[i].student_count++;
            printf("%s 分配到宿舍 %d\n", student.name, dormitories[i].dorm_number);
            return;
        }
    }
    printf("没有空闲的宿舍床位\n");
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
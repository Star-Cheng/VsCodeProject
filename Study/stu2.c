#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    char nativePlace[50];
    char hobby[50];
    char ethnicity[50];
    char religion[50];
    // 可以根据需要添加其他属性
};

void assignDorm(struct Student students[], int numStudents) {
    // 宿舍分配算法的实现
    // 根据宗教、籍贯、兴趣爱好等因素进行分配
    // 这里只是一个简单的示例，实际的宿舍分配算法可能需要更复杂的逻辑
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].religion, "Christianity") == 0) {
            printf("%s 分配到基督教宿舍\n", students[i].name);
        } else if (strcmp(students[i].religion, "Islam") == 0) {
            printf("%s 分配到伊斯兰教宿舍\n", students[i].name);
        } else {
            printf("%s 分配到其他宿舍\n", students[i].name);
        }
    }
}

int main() {
    struct Student students[5] = {{"张三", 1, "北京", "篮球", "汉族", "Christianity"},
                                  {"李四", 2, "上海", "足球", "回族", "Islam"},
                                  {"王五", 3, "广州", "乒乓球", "满族", "Buddhism"},
                                  {"赵六", 4, "深圳", "游泳", "汉族", "Christianity"},
                                  {"钱七", 5, "重庆", "跑步", "藏族", "Buddhism"}};

    assignDorm(students, 5);

    return 0;
}

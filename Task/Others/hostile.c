#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 定义病人结构体
typedef struct {
    char name[50];
    int age;
    char symptom[100];
    int urgencyLevel;  // 紧急程度：1, 2, 3...
} Patient;

// 定义医生结构体
typedef struct {
    int isBusy;  // 0: 空闲, 1: 忙碌
} Doctor;

int main() {
    Doctor doctor = {0};  // 初始医生状态为空闲

    // 病人队列（简化为一个数组）
    Patient waitingQueue[100];
    int queueSize = 0;

    // 获取当前时间
    time_t currentTime;
    struct tm *localTime;

    while (1) {
        time(&currentTime);
        localTime = localtime(&currentTime);

        int hour = localTime->tm_hour;

        // 检查医生工作时间
        if (hour < 8 || hour >= 17) {
            printf("非工作时间，医生休息中！\n");
            continue;
        }

        // 病人信息录入
        Patient newPatient;
        printf("请输入病人姓名：");
        scanf("%s", newPatient.name);
        printf("请输入病人年龄：");
        scanf("%d", &newPatient.age);
        printf("请输入病人症状：");
        scanf("%s", newPatient.symptom);
        printf("请输入病人紧急程度（1, 2, 3...）：");
        scanf("%d", &newPatient.urgencyLevel);

        // 添加到等待队列
        waitingQueue[queueSize++] = newPatient;

        // 搜索病人信息
        char searchName[50];
        printf("请输入要搜索的病人姓名：");
        scanf("%s", searchName);

        for (int i = 0; i < queueSize; i++) {
            if (strcmp(waitingQueue[i].name, searchName) == 0) {
                printf("找到病人信息：姓名：%s, 年龄：%d, 症状：%s, 紧急程度：%d\n",
                       waitingQueue[i].name, waitingQueue[i].age, waitingQueue[i].symptom, waitingQueue[i].urgencyLevel);
                break;
            }
        }

        // 病人等待时间提醒（简化为等待5分钟提醒）
        for (int i = 0; i < queueSize; i++) {
            // 检查时间差（需要根据实际需求来实现）
            // ...

            // 如果时间差满足条件，提醒
            printf("病人等待时间超过阈值，请注意！\n");
        }

        // 医生状态管理（处理完一个病人后更新状态）
        doctor.isBusy = 1;  // 假设医生忙碌
        // 处理病人...
        doctor.isBusy = 0;  // 更新为医生空闲
    }

    return 0;
}

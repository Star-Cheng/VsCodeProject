#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 客房结构体
typedef struct {
    int room_number;
    char type[20];
    char status[20];
    float price;
} Room;

// 旅客结构体
typedef struct {
    char id[20];
    char name[50];
    char phone[20];
    int room_number;
    float price;
    char check_in_date[20];
    char check_out_date[20];
    float deposit;
} Guest;

// 函数声明
void add_room(Room rooms[], int *num_rooms);
void display_rooms(Room rooms[], int num_rooms);
void check_in(Guest guests[], int *num_guests, Room rooms[], int num_rooms);
void check_out(Guest guests[], int num_guests, Room rooms[], int num_rooms);
void statistics(Guest guests[], int num_guests, Room rooms[], int num_rooms);

int main() {
    Room rooms[100]; // 最多100个客房
    Guest guests[100]; // 最多100个旅客
    int num_rooms = 0;
    int num_guests = 0;
    int choice;

    do {
        printf("\n1. 录入客房信息\n");
        printf("2. 查询客房信息\n");
        printf("3. 入住业务\n");
        printf("4. 退房业务\n");
        printf("5. 统计查询\n");
        printf("6. 退出系统\n");
        printf("请选择[1/2/3/4/5/6]：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_room(rooms, &num_rooms);
                break;
            case 2:
                display_rooms(rooms, num_rooms);
                break;
            case 3:
                check_in(guests, &num_guests, rooms, num_rooms);
                break;
            case 4:
                check_out(guests, num_guests, rooms, num_rooms);
                break;
            case 5:
                statistics(guests, num_guests, rooms, num_rooms);
                break;
            case 6:
                printf("感谢使用，再见！\n");
                break;
            default:
                printf("请选择正确的操作！\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

void add_room(Room rooms[], int *num_rooms) {
    printf("请输入房间号：");
    scanf("%d", &rooms[*num_rooms].room_number);
    printf("请输入房间类型（大床/标间）：");
    scanf("%s", rooms[*num_rooms].type);
    printf("请输入房间状态（已住/空闲）：");
    scanf("%s", rooms[*num_rooms].status);
    printf("请输入房间单价：");
    scanf("%f", &rooms[*num_rooms].price);
    
    (*num_rooms)++;
}

void display_rooms(Room rooms[], int num_rooms) {
    int i;
    
    printf("房间号\t类型\t状态\t单价\n");
    for (i = 0; i < num_rooms; i++) {
        printf("%d\t%s\t%s\t%.2f\n", rooms[i].room_number, rooms[i].type, rooms[i].status, rooms[i].price);
    }
}

void check_in(Guest guests[], int *num_guests, Room rooms[], int num_rooms) {
    int room_number, i;
    float discount = 1.0;
    
    // 输入客房号
    printf("请输入客房号：");
    scanf("%d", &room_number);

    // 查找客房
    for (i = 0; i < num_rooms; i++) {
        if (rooms[i].room_number == room_number) {
            break;
        }
    }

    // 判断客房是否存在
    if (i == num_rooms) {
        printf("客房号不存在！\n");
        return;
    }

    // 判断客房是否已住
    if (strcmp(rooms[i].status, "已住") == 0) {
        printf("客房已被占用！\n");
        return;
    }

    // 输入客户信息
    printf("请输入身份证号：");
    scanf("%s", guests[*num_guests].id);
    printf("请输入姓名：");
    scanf("%s", guests[*num_guests].name);
    printf("请输入手机号：");
    scanf("%s", guests[*num_guests].phone);
    printf("请输入入住日期：");
    scanf("%s", guests[*num_guests].check_in_date);
    printf("请输入离店日期：");
    scanf("%s", guests[*num_guests].check_out_date);

    // 判断是否团队客户
    int num_people;
    printf("请输入入住人数：");
    scanf("%d", &num_people);
    if (num_people >= 20) {
        discount = 0.8; // 20人以上优惠20%
    } else if (num_people >= 10) {
        discount = 0.9; // 10人以上优惠10%
    }

    // 计算价格并记录客房信息
    guests[*num_guests].room_number = room_number;
    guests[*num_guests].price = rooms[i].price * discount;
    strcpy(rooms[i].status, "已住");

    // 提示成功入住
    printf("入住成功！\n");

    (*num_guests)++;
}

void check_out(Guest guests[], int num_guests, Room rooms[], int num_rooms) {
    int room_number, i, j;
    float damage_fee = 0.0;
    
    // 输入客房号
    printf("请输入客房号：");
    scanf("%d", &room_number);

    // 查找客房
    for (i = 0; i < num_guests; i++) {
        if (guests[i].room_number == room_number) {
            break;
        }
    }

    // 判断客房是否入住
    if (i == num_guests) {
        printf("客房号未入住！\n");
        return;
    }

    // 输入实际离店日期
    printf("请输入实际离店日期：");
    scanf("%s", guests[i].check_out_date);

    // 计算住宿费用
    float days = 1; // 简化计算，实际应根据日期计算天数
    float total_price = guests[i].price * days;

    // 判断是否有物品损坏
    printf("是否有物品损坏（是/否）：");
    char answer[5];
    scanf("%s", answer);
    if (strcmp(answer, "是") == 0) {
        printf("请输入损坏物品的赔偿费用：");
        scanf("%f", &damage_fee);
    }

    // 结算费用并更新客房状态
    guests[i].price = total_price + damage_fee;
    for (j = 0; j < num_rooms; j++) {
        if (rooms[j].room_number == room_number) {
            strcpy(rooms[j].status, "空闲");
            break;
        }
    }

    // 提示成功退房
    printf("退房成功！\n");
}

void statistics(Guest guests[], int num_guests, Room rooms[], int num_rooms) {
    int i;
    float total_income = 0;
    int occupied_rooms = 0;
    int vacant_rooms = 0;

    // 统计当日入住信息和剩余房源情况
    for (i = 0; i < num_guests; i++) {
        total_income += guests[i].price;
    }
    for (i = 0; i < num_rooms; i++) {
        if (strcmp(rooms[i].status, "已住") == 0) {
            occupied_rooms++;
        } else {
            vacant_rooms++;
        }
    }

    // 显示统计结果
    printf("当日入住人数：%d\n", num_guests);
    printf("当日营业额：%.2f\n", total_income);
    printf("剩余空闲房间数：%d\n", vacant_rooms);
}

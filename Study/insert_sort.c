#include <stdio.h>

//插入排序
void insertSort(int arry[], int len)
{
        int i;
        int temp;//保存要插入的元素
        int j;//从当前要要比较插入的元素的前面一个开始
        for ( i = 1; i < len; i++)//第一个元素视为有序,把后面的元素一个一个的插入到前面
        {
                temp = arry[i];
                j = i - 1;
                while (j >= 0&&arry[j]>temp)
                {
                        arry[j + 1] = arry[j];//前面的元素往后面移动
                        j--;
                }
                arry[j + 1] = temp;//把要插入的元素,插入进对应的位置
        }
}

//输出
void print(int arry[], int len)
{
        for (int i = 0; i < len; i++)
        {
                printf("%d ", arry[i]);
        }
}
int main()
{
        int arry[10]={3,44,38,5,47,15,36,26,27,2};
        insertSort(arry,10);
        print(arry,10);


        printf("\n");
        return 0;
}

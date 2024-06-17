#include <stdio.h>

//冒泡排序
void BubbleSort(int arry[],int len)
{
        int i;
        int j;
        int temp;
        for(i=0;i<len-1;i++)//比较次数
        {
                for(j=0;j<len-1-i;j++)//比较过程
                {
                        if(arry[j]<arry[j+1]) //比较大小
                        {
                                temp=arry[j];
                                arry[j]=arry[j+1];
                                arry[j+1]=temp;

                        }
                }

        }

}
//输出
void print(int arry[],int len)
{
        int i;
        for(i=0;i<len;i++)
        {
                printf("%d ",arry[i]);
        }
}
int main()
{

        int arry[10]={9,3,56,44,77,88,54,79,52,111};

        BubbleSort(arry,10);
        print(arry,10);
        printf("\n");

        return 0;
}

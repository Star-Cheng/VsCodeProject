#include <stdio.h>

//快速排序
void quickSort(int arry[], int low, int high)
{
        if (low > high)
        {
                return;
        }
        int i = low, j = high, temp = arry[i];//获取左右和基准数
        while (i < j)
        {
                while (temp < arry[j] && i < j)
                {
                        j--;
                }
                if (i < j)
                  {
                        arry[i++] = arry[j];
                  }
                while (temp>arry[i] && i < j)
                    {

                        i++;
                     }
                if (i < j)
                    {
                        arry[j--] = arry[i];
                    }
        }
        arry[i] = temp;

        quickSort(arry, low, i - 1);//左边
        quickSort(arry, i + 1, high);//右边
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

        int arry[15]={7,44,38,99,47,15,36,26,27,2,46,43,19,50,48};
        quickSort(arry,0,14);
        print(arry,15);
        
        printf("\n");
        return 0;
}        
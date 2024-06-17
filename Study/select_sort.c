#include<stdio.h>
void SelectSort(int arr[],int len)
{
    int i,j;
    for(i=0;i<len-1;i++)
    {
        int bacis = i;
        for(j=i+1;j<len;j++)
        {
            if(arr[j]>arr[bacis])
            {
                bacis = j;
            }
        }
        int temp=arr[bacis];
        arr[bacis]=arr[i];
        arr[i]=temp;
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


	// 1、用户输入数组的长度
    int i,len;
    printf("请输入数组的长度：\n"); 
	scanf("%d",&len);
	printf("您输入的数组长度为：%d\n",len);

	// 2、根据用户输入的长度创建数组
    int arry[len];


    for(i=0;i<len;i++)
    {
        printf("请输入array[%d]的值:\n",i);
        // scanf("%d",&array[i]);//(使用这种，或者下面的 scanf("%d",array+i); 都是等价的)
        scanf("%d",arry+i);
    }

    SelectSort(arry,len);
    print(arry,len);


    printf("\n");
    return 0;
}
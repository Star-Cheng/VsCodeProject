#include <stdio.h>
void fun(char *s,char c)
{
        int i,j,n;
        for (i=0;s[i]!='\0';i++)
        {
                if(s[i]==c)
                {
                        n=0;
                        while(s[i+1+n]!='\0') 
                        {
                                n++;
                                for(i=i+n+1;j>i;j--)
                                {                                
                                        s[j+1]=s[j];
                                }
                                s[j+1]=c;
                                i=i+1;
                        }

                }
        }
}

int main()
{
        char s[80]="baacda";
        char c='a';
        fun(s,c);
        printf("result:%s\n",s);
        return 0;
}
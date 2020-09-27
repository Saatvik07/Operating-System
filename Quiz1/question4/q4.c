#include<stdio.h>
int long_add(int,int,int,int);
int main(){
    int variable1;
    int variable2;
    int variable3,variable4;
    printf("Enter the first number ");
    scanf("%d", &variable1 );
    printf("Enter the second number ");
    scanf("%d", &variable2);
    printf("Enter the third number ");
    scanf("%d", &variable3);
    printf("Enter the fourth number ");
    scanf("%d", &variable4);
    printf("%d + %d + %d + %d = %d\n",variable1,variable2,variable3,variable4,long_add(variable1,variable2,variable3,variable4));
    return 0;
}
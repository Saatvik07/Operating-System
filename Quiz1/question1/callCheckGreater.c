#include<stdio.h>
void checkGreater(int,int);
int main(){
    int variable1;
    int variable2;
    printf("Enter the first number ");
    scanf("%d", &variable1 );
    printf("Enter the second number ");
    scanf("%d", &variable2);
    checkGreater(variable1,variable2);
    return 0;
}
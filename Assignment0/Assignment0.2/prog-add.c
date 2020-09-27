#include<stdio.h>
#include <inttypes.h>
int64_t add(int64_t, int64_t);
int main(){
    int64_t variable1;
    int64_t variable2;
    printf("Enter the first number ");
    scanf("%ld", &variable1 );
    printf("Enter the second number ");
    scanf("%ld", &variable2);
    int64_t answer = add(variable1,variable2);
    printf("%ld + %ld = %ld\n", variable1,variable2,answer);
    return 0;
}
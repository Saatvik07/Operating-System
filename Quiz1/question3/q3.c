#include<stdio.h>
#include <inttypes.h>
int main(){
    char x[64];
    int64_t *long_int_ptr = (int64_t*)&x;
    for(int i=0;i<=7;i++){
        int64_t num = (int64_t)i;
        *long_int_ptr = num;
        long_int_ptr++;
    }
    long_int_ptr= (int64_t*)&x;
    printf("Array of 8 64-bit integers ");
    for(int i=0;i<=7;i++){
        printf("%ld ",*long_int_ptr);
        long_int_ptr++;
        
    }
    printf("\n");
    int *int_ptr = (int*)&x;
    printf("Array of 16 32-bit integers ");
    for(int i=0;i<=15;i++){
        *int_ptr = i;
        int_ptr++;
    }
    int_ptr = (int*)&x;
    for(int i=0;i<=15;i++){
        printf("%d ",*int_ptr);
        int_ptr++;
    }
    return 0;
}
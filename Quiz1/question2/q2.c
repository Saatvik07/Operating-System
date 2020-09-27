#include<stdio.h>
#include<math.h>
float add(float a,float b){
    return (float)(round(a)+round(b));
}
int main(){
    printf("Sum of two decimal numbers %f",add(1.5,2.6));
    return 0;
}
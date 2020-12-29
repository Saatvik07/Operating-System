#include<stdio.h>
int main(){
    char name[8]= "Saatvik\0";
    printf("Reading the name from the main memory: %s\n",name);
    return 0;
}
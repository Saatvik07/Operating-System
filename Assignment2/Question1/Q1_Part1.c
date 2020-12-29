//Saatvik Bhatnagar 2019097
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
    int globalVar = 10;
    pid_t childPID = fork();
    if(childPID <0){
        printf("%s\n","Fork Failed");
        return -1;
    }
    else if (childPID==0){
        while (globalVar>-90)
        {
            globalVar--;
             printf("%d\n",globalVar);
        }
        printf("Printing from inside the child process: %d\n",globalVar);
        exit(0);
    }
    else{
        while(globalVar<100){
            globalVar++;
             printf("%d\n",globalVar);
        }
        printf("Printing from inside the parent process: %d\n",globalVar);
        return 0;
    }
}

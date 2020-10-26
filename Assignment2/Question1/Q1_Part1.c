#include<unistd.h>
#include<stdio.h>
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
        }
        printf("Printing from inside the child process: %d\n",globalVar);
    }
    else{
        while(globalVar<100){
            globalVar++;
        }
        printf("Printing from inside the parent process: %d\n",globalVar);
    }
}
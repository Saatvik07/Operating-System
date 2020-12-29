//Saatvik Bhatnagar 2019097
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
int globalVariable = 10;
void* child(void* args){
    while (globalVariable >-90)
    {
        globalVariable--;
        printf("%d\n",globalVariable);
    }
    printf("Printing from the child thread %d\n",globalVariable);
    pthread_exit(NULL);
}
int main (){
    pthread_t childPID;
    pthread_create(&childPID,NULL,child,NULL);
    pthread_join(childPID,NULL);
    while (globalVariable<100)
    {
        globalVariable++;
        printf("%d\n",globalVariable);
    }
    printf("Printing from the parent thread %d\n",globalVariable);
    return 0;
}

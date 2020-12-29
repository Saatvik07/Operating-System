/* Name: Saatvik Bhatnagar
	Roll_Number: 2019097 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct cSem
{
    pthread_cond_t threadBlocker;
    pthread_mutex_t mutex;
    int flag;
} sem1;
void cSemInit(sem1 **s, int initValue)
{
    *s = (sem1 *)malloc(sizeof(sem1));
    pthread_mutex_init(&((*s)->mutex), NULL);
    pthread_cond_init(&((*s)->threadBlocker), NULL);
    (*s)->flag = initValue;
}
void cSemWait(sem1 *s)
{
    pthread_mutex_lock(&(s->mutex));
    while (s->flag == 0)
    {
        pthread_cond_wait(&(s->threadBlocker), &(s->mutex));
    }
    s->flag--;
    pthread_mutex_unlock(&(s->mutex));
}
void cSemPost(sem1 *s)
{
    pthread_mutex_lock(&(s->mutex));
    pthread_cond_signal(&(s->threadBlocker));
    s->flag++;

    pthread_mutex_unlock(&(s->mutex));
}
void cSemPostPrint(sem1 *s, char *name)
{
    pthread_mutex_lock(&(s->mutex));
    pthread_cond_signal(&(s->threadBlocker));
    s->flag++;
    printf("%s semValue:%d\n", name, s->flag);
    pthread_mutex_unlock(&(s->mutex));
}
int cSemWaitNoBlock(sem1 *s)
{
    int ret = pthread_mutex_trylock(&(s->mutex));
    if (ret != 0)
    {
        return ret;
    }
    while (s->flag == 0)
    {
        pthread_cond_wait(&(s->threadBlocker), &(s->mutex));
    }
    s->flag--;
    pthread_mutex_unlock(&(s->mutex));
}
int cSemPostNoBlock(sem1 *s)
{
    int ret = pthread_mutex_trylock(&(s->mutex));
    if (ret != 0)
    {
        return ret;
    }
    pthread_cond_signal(&(s->threadBlocker));
    s->flag++;
    pthread_mutex_unlock(&(s->mutex));
}
int cSemPostNoBlockPrint(sem1 *s, char *name)
{
    int ret = pthread_mutex_trylock(&(s->mutex));
    if (ret != 0)
    {
        return ret;
    }
    pthread_cond_signal(&(s->threadBlocker));
    s->flag++;
    printf("%s semValue:%d\n", name, s->flag);
    pthread_mutex_unlock(&(s->mutex));
}
sem1 *numPhilRoom, *bowls;
sem1 *forks[1000000];
int x = 0;
int k=0;
void *philosopher(void *num)
{
    while (1)
    {
        int philID = *(int *)num;
        cSemWait(numPhilRoom);
        printf("Philosoper %d has entered room\n", philID);
        cSemWait(forks[philID]);
        cSemWait(forks[(philID + 1) % k]);
        cSemWait(bowls);
        cSemWait(bowls);
        printf("Philosopher %d is eating using forks %d and %d\n", philID, philID, (philID + 1) % k);
        sleep(2);
        cSemPostPrint(bowls, "Bowl 1");
        cSemPostPrint(bowls, "Bowl 2");
        char str[256];
        sprintf(str, "Fork %d", philID);
        cSemPostPrint(forks[philID], str);
        sprintf(str, "Fork %d", (philID + 1) % k);
        cSemPostPrint(forks[(philID + 1) % k], str);
        cSemPostPrint(numPhilRoom, "Room");
        printf("Philosopher %d has eaten and exited ;)\n", philID);
        sleep(2);
    }
}
void *philosopherNoBlock(void *num)
{
    while (1)
    {
        int philID = *(int *)num;
        char str[256], str2[256];
        sprintf(str, "Fork %d", philID);
        sprintf(str2, "Fork %d", (philID + 1) % k);
        int ret1 = cSemWaitNoBlock(numPhilRoom);
        if (ret1 != 0)
        {
            printf("Entry in room failed for philosopher %d\n", philID);
            continue;
        }

        printf("Philosoper %d has entered room\n", philID);
        int ret2 = cSemWaitNoBlock(forks[philID]);
        if (ret2 != 0)
        {
            printf("Picking up fork %d failed for philosopher %d\n", philID, philID);
            int ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            }
            
            continue;
        }
        int ret3 = cSemWaitNoBlock(forks[(philID + 1) % k]);
        if (ret3 != 0)
        {
            printf("Picking up fork %d failed for philosopher %d\n", (philID + 1) % k, philID);
            int ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            }
            ret = cSemPostNoBlockPrint(forks[philID], str);
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(forks[philID], str);
            }
            continue;
        }
        int ret4 = cSemWaitNoBlock(bowls);
        if (ret4 != 0)
        {
            printf("Picking up bowl %d failed for philosopher %d\n", 1, philID);
            int ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            }
            ret = cSemPostNoBlockPrint(forks[philID], str);
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(forks[philID], str);
            }
            ret = cSemPostNoBlockPrint(forks[(philID + 1) % k], str2);
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(forks[(philID + 1) % k], str2);
            }
            continue;
        }
        int ret5 = cSemWaitNoBlock(bowls);
        if (ret5 != 0)
        {
            printf("Picking up bowl %d failed for philosopher %d\n", 2, philID);
            int ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(numPhilRoom, "Room");
            }
            ret = cSemPostNoBlockPrint(forks[philID], str);
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(forks[philID], str);
            }
            ret = cSemPostNoBlockPrint(forks[(philID + 1) % k], str2);
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(forks[(philID + 1) % k], str2);
            }
            ret = cSemPostNoBlockPrint(bowls, "Bowl 1");
            while(ret !=0){
            	ret = cSemPostNoBlockPrint(bowls, "Bowl 1");
            }
            continue;
        }
        printf("Philosopher %d is eating using forks %d and %d\n", philID, philID, (philID + 1) % k);
        sleep(2);
        cSemPost(forks[philID]);
        cSemPost(forks[(philID + 1) % k]);
        cSemPost(bowls);
        cSemPost(bowls);
        printf("Philosopher %d has eaten and exited ;)\n", philID);
        //printf("Philosopher %d has eaten and exited ;)\n", philID);
        cSemPost(numPhilRoom);
        sleep(2);
    }
}
int main()
{
    
    printf("Enter the number of philosophers: ");
    scanf("%d",&k);
    int choice;
    printf("1. Blocking\n 2.Non-Blocking\nEnter your choice: ");
    scanf("%d",&choice);
    int a[k];
    pthread_t tid[k];
    cSemInit(&numPhilRoom, k-1);
    cSemInit(&bowls, 2);
    for (int i = 0; i < k; i++)
    {
        cSemInit(&forks[i], 1);
    }
    for (int i = 0; i < k; i++)
    {
        a[i] = i;
        if(choice==1){
        	pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
        }
        else{
        	pthread_create(&tid[i], NULL, philosopherNoBlock, (void *)&a[i]);
        }
        
    }

    for (int i = 0; i < k; i++)
    {
        pthread_join(tid[i], NULL);
    }
}

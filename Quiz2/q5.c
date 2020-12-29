#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <fcntl.h>
pthread_mutex_t mutex;
sem_t *wrt;
int readerNum = 0;
pthread_t writerID;
pthread_t readerID[10];
key_t segmentKey = 0x100;
char *segmentFirstAddr;
void *reader(void *arg1)
{
    pthread_mutex_lock(&mutex);
    readerNum++;
    if (readerNum == 1)
    {
        sem_wait(wrt);
    }
    printf("Reader %d: Info in the shared memory is %s\n", *((int *)arg1), segmentFirstAddr);
    readerNum--;
    if (readerNum == 0)
        sem_post(wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg2)
{
    sem_wait(wrt);
    sprintf(segmentFirstAddr,"%d",*((int *)arg2));
    printf("Writer %d: Info written in the shared memory is %s\n", *((int *)arg2), segmentFirstAddr);
    sem_post(wrt);
    return NULL;
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    sem_unlink("write");
    wrt = sem_open("write", O_CREAT, 0660, 1);
    int segmentID = shmget(segmentKey, 8, 0666 | IPC_CREAT);
    segmentFirstAddr = (char *)shmat(segmentID, (void *)0, 0);
    strcpy(segmentFirstAddr, "Mazel Tov");
    int a=1;
    int b[10] = {1,2,3,4,5,6,7,8,9,10};
    pthread_create(&writerID, NULL, writer, (void *)&a);
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&(readerID[i]), NULL, reader, (void *)&b[i]);
    }
    
    for (int i = 0; i < 10; i++)
    {
        pthread_join(readerID[i], NULL);
    }
    pthread_join(writerID, NULL);
    
    
}

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
char *str;
int *num;
pthread_t tid1, tid2;
int textID, numID;
sem_t *write1, *read1, *parent_read_complete, *child_read_complete;
int main()
{
    sem_unlink("read");
    sem_unlink("write");
    write1 = sem_open("write", O_CREAT, 0660, 0);
    read1 = sem_open("read", O_CREAT, 0660, 1);
    sem_unlink("parent");
    sem_unlink("child");
    parent_read_complete = sem_open("parent", O_CREAT, 0660, 0);
    child_read_complete = sem_open("child", O_CREAT, 0660, 1);
    pid_t p;
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    else if (p > 0)
    {
        key_t textKey2 = 0x400;
        int textID = shmget(textKey2, 1024, 0666 | IPC_CREAT);
        if (textID < 0)
        {
            perror("Key is wrong");
        }
        char *output = (char *)shmat(textID, (void *)0, 0);
        key_t numKey2 = 0x500;
        int numID = shmget(numKey2, 1024, 0666 | IPC_CREAT);
        if (numID < 0)
        {
            perror("Key is wrong");
        }
        int *number = (int *)shmat(numID, (void *)0, 0);
        int i = 0;
        do
        {
            sem_wait(write1);

            printf("Data read from text memory segment by parent: %s\n", output);

            printf("Data read from number memory segment by parent: %d\n", number[0]);

            sem_post(read1);
        } while (number[0] < 20);
        sem_post(parent_read_complete);
        while (i <= 20)
        {
            sem_wait(read1);
            strcpy(output, "Parent's write");
            number[0] = i;
            sem_post(write1);

            i++;
        }

        sem_wait(child_read_complete);
        shmdt(number);
        shmctl(numID, IPC_RMID, NULL);
        shmdt(output);
        shmctl(textID, IPC_RMID, NULL);
    }

    // child process
    else
    {

        key_t textKey = 0x400;
        textID = shmget(textKey, 1024, 0666 | IPC_CREAT);
        if (textID < 0)
        {
            perror("Key is wrong");
        }
        key_t numKey = 0x500;
        numID = shmget(numKey, 1024, 0666 | IPC_CREAT);
        if (numID < 0)
        {
            perror("Key is wrong");
        }
        str = (char *)shmat(textID, (void *)0, 0);
        num = (int *)shmat(numID, (void *)0, 0);
        int i = 0;
        while (i <= 20)
        {
            sem_wait(read1);
            strcpy(str, "Child's write");
            num[0] = i;
            sem_post(write1);
            i++;
        }

        sem_wait(parent_read_complete);
        do
        {
            sem_wait(write1);

            printf("Data read from text memory segment by child: %s\n", str);

            printf("Data read from number memory segment by child: %d\n", num[0]);

            sem_post(read1);
        } while (num[0] < 20);
        sem_post(child_read_complete);
        exit(0);
    }
}


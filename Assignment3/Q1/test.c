/* Name: Saatvik Bhatnagar
	Roll_Number: 2019097 */
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
    int pipeEnds[2];
    long sRTGuarantee;
    printf("Enter the soft real time guarantee in microseconds ");
    scanf("%ld",&sRTGuarantee);
    printf("RT guarantee %ld\n",sRTGuarantee);
    double process2ExecTime=0;
    if(pipe(pipeEnds)==-1){
    	printf("%s\n","Pipe failed");
    	return -1;
    }
    long pid, tem, i = 0;
    pid_t process2ID = fork();
    if (process2ID < 0)
    {
        printf("%s\n", "Fork Failed");
        return -1;
    }
    if (process2ID > 0)
    {
        long result = syscall(335, process2ID, sRTGuarantee);
        if(result<0){
        	perror("Error: ");
        	return result;
        }
        printf("Process2 ID: %d  Process1 ID: %d\n", process2ID, (int)getpid());
        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        for (i = 0; i < 100000000; i++);
        gettimeofday(&t2, NULL);
        double execTime = (double)(t2.tv_usec - t1.tv_usec) / 1000 + (double)(t2.tv_sec - t1.tv_sec) * 1000;
        printf("Time for Process1: %lf\n", execTime);
        wait(NULL);
        close(pipeEnds[1]);
        read(pipeEnds[0],&process2ExecTime,sizeof(process2ExecTime));
        close(pipeEnds[0]);
        printf("The difference due to addition of soft real time guarantee %lf\n",execTime-process2ExecTime);
    }
    else
    {
        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        for (i = 0; i < 100000000; i++);
        gettimeofday(&t2, NULL);
        double execTime = (double)(t2.tv_usec - t1.tv_usec) / 1000 + (double)(t2.tv_sec - t1.tv_sec) * 1000;
        printf("Time for Process2: %lf\n", execTime);
        close(pipeEnds[0]);
        write(pipeEnds[1],&execTime,sizeof(execTime));
        close(pipeEnds[1]);
        exit(0);
    }
    return 0;
}

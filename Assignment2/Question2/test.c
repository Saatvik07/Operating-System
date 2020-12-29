#define _GNU_SOURCE
//Saatvik Bhatnagar 2019097
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * Put your syscall number here.
 */
#define SYS_sh_task_info 336

int main(int argc, char **argv)
{
  char *arg = argv[1];
  int x = atoi(arg);
  long result = syscall(SYS_sh_task_info, x, argv[2]);
  if(result<0)
  	perror("Error:");
  printf("System call returned %ld.\n", res);
  return result;
}


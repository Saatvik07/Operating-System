#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

int main()
{
    int firstPipeEnds[2];  
    int secondPipeEnds[2];

    char input_str[512];

    if (pipe(firstPipeEnds) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(secondPipeEnds) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    fgets(input_str, 512, stdin);
    pid_t p;
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    else if (p > 0)
    {
        char output_str[512];
        close(firstPipeEnds[0]);
        write(firstPipeEnds[1], input_str, strlen(input_str) + 1);
        close(firstPipeEnds[1]);
        wait(NULL);

        close(secondPipeEnds[1]);
        read(secondPipeEnds[0], output_str, 512);
        printf("Uppercase String %s\n", output_str);
        close(secondPipeEnds[0]);
    }

    // child process
    else
    {
        close(firstPipeEnds[1]);

        char input_str[512];
        char output_str[512];
        read(firstPipeEnds[0], input_str, 100);
        int i = 0, j = 0;
        char upperCh;
        while (input_str[i] != '\n')
        {
            if (input_str[i] == '\\')
            {
                switch (input_str[i + 1])
                {
                case 't':
                    output_str[j] = '\t';
                    break;
                case 'a':
                    output_str[j] = '\a';
                    break;
                case 'b':
                    output_str[j] = '\b';
                    break;
                case 'f':
                    output_str[j] = '\f';
                    break;
                case 'r':
                    output_str[j] = '\r';
                    break;
                case 'v':
                    output_str[j] = '\v';
                    break;
                case '\\':
                    output_str[j] = '\\';
                    break;
                case '\'':
                    output_str[j] = '\'';
                    break;
                case '\"':
                    output_str[j] = '\"';
                    break;
                case '\?':
                    output_str[j] = '\?';
                    break;
                }
                i += 2;
            }
            else
            {
                upperCh = input_str[i];
                output_str[j] = toupper(upperCh);
                i++;
            }
            j++;
        }
        output_str[j] = '\0';

	close(secondPipeEnds[0]);
        close(firstPipeEnds[0]);

        write(secondPipeEnds[1], output_str, strlen(output_str) + 1);
        close(secondPipeEnds[1]);

        exit(0);
    }
}


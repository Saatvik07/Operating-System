#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
int presentActivity[5];
int philosophers[5] = {0, 1, 2, 3, 4};

sem_t globalSemaphore;
sem_t individualSemaphore[5];

void test(int id)
{
    if (presentActivity[id] == 1 && presentActivity[(id + 4) % 5] != 0 && presentActivity[(id + 1) % 5] != 0)
    {
        presentActivity[id] = 0;

        sleep(2);

        printf("Philosopher %d takes chopsticks %d and %d\n",
               id + 1, (id + 4) % 5 + 1, id + 1);

        printf("Philosopher %d is Eating\n", id + 1);
        sem_post(&individualSemaphore[id]);
    }
}
void pickup_chopsticks(int id)
{
    sem_wait(&globalSemaphore);
    presentActivity[id] = 1;
    printf("Philosopher %d is Hungry\n", id + 1);
    test(id);
    sem_post(&globalSemaphore);
    sem_wait(&individualSemaphore[id]);
    sleep(1);
}
void putdown_chopsticks(int id)
{

    sem_wait(&globalSemaphore);
    presentActivity[id] = 2;

    printf("Philosopher %d putting chopsticks %d and %d down\n", id + 1, (id + 4) % 5 + 1, id + 1);
    printf("Philosopher %d is thinking\n", id + 1);

    test((id + 4) % 5);

    test((id + 1) % 5);

    sem_post(&globalSemaphore);
}

void *philosopher_thread(void *num)
{
    int *i = num;
    sleep(1);
    pickup_chopsticks(*i);
    sleep(0);
    putdown_chopsticks(*i);
}

int main()
{
    int i;
    pthread_t thread_id[5];
    sem_init(&globalSemaphore, 0, 1);
    for (i = 0; i < 5; i++)
    {
        sem_init(&individualSemaphore[i], 0, 0);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher_thread, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < 5; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
}

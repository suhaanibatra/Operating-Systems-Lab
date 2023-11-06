#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
void *thread_function(void *arg)
{
    sem_wait(&semaphore);
    printf("Thread %d entered critical section.\n", *(int *)arg);
    _sleep(2);
    printf("Thread %d exited critical section.\n", *(int *)arg);
    sem_post(&semaphore);
    return NULL;
}
int main()
{
    sem_init(&semaphore, 0, 1);
    pthread_t thread1, thread2;
    int thread1_id = 1, thread2_id = 2;
    pthread_create(&thread1, NULL, thread_function, &thread1_id);
    pthread_create(&thread2, NULL, thread_function, &thread2_id);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);
    return 0;
}
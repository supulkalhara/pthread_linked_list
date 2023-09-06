#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedList.h"

int thread_count;
int n;
int16_t m;
float m_member, m_insert, m_delete;
int member_count, insert_count, delete_count;
int member_count_per_thread, insert_count_per_thread, delete_count_per_thread;
struct list_node_s *head_p;
pthread_rwlock_t list_rw_lock;

void *RandomTaskHandler(void *rank);

int main(int argc, char *argv[])
{
    long thread;
    pthread_t *thread_handles;
    clock_t start_time, end_time;
    double cpu_time_used;

    pthread_rwlock_init(&list_rw_lock, NULL);

    srand(time(NULL));

    thread_count = strtol(argv[1], NULL, 10);
    n = strtol(argv[2], NULL, 10);
    m = strtol(argv[3], NULL, 10);
    m_member = strtod(argv[4], NULL);
    m_insert = strtod(argv[5], NULL);
    m_delete = strtod(argv[6], NULL);

    char* filename = argv[7];

    member_count = m * m_member;
    insert_count = m * m_insert;
    delete_count = m * m_delete;

    member_count_per_thread = member_count / thread_count;
    insert_count_per_thread = insert_count / thread_count;
    delete_count_per_thread = delete_count / thread_count;

    DisplayStatistics("Member Statistics", member_count, member_count_per_thread);
    DisplayStatistics("Insert Statistics", insert_count, insert_count_per_thread);
    DisplayStatistics("Delete Statistics", delete_count, delete_count_per_thread);

    head_p = malloc(sizeof(struct list_node_s));
    Populate(head_p, n);

    start_time = clock();

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, RandomTaskHandler, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / (CLOCKS_PER_SEC);
    printf(" Start to End Duration (CPU): %f s\n", cpu_time_used);

    pthread_rwlock_destroy(&list_rw_lock);

    FILE *fp = fopen(filename, "a");
    fprintf(fp, "%lf\n", cpu_time_used);
    fclose(fp);

    return 0;
}

// Assign a task to thread
void *RandomTaskHandler(void *rank)
{
    long my_rank = (long)rank;

    int (*functions[])() = {Member, Insert, Delete};
    int counts_per_thread[] = {member_count_per_thread, insert_count_per_thread, delete_count_per_thread};

    int totalCalls_per_thread = member_count_per_thread + insert_count_per_thread + delete_count_per_thread;

    // Execute calls assigned to thread
    while (totalCalls_per_thread > 0)
    {
        int randomIndex = rand() % 3;

        // Pick a task out of remaining task
        if (counts_per_thread[randomIndex] > 0)
        {
            // If the task is a Member function
            if (randomIndex == 0)
            {   
                //Engage read lock
                pthread_rwlock_rdlock(&list_rw_lock);
            }
            else
            {
                // Engage write lock for insert and delete
                pthread_rwlock_wrlock(&list_rw_lock);
            }

            // Perform task on the linked list
            functions[randomIndex](RandomIntegerGenerator(), &head_p);

            //Release read write lock
            pthread_rwlock_unlock(&list_rw_lock);

            counts_per_thread[randomIndex]--;
            totalCalls_per_thread--;
        }
    }

    return NULL;
}
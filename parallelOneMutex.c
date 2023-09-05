#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int n;
int16_t m;
float m_member, m_insert, m_delete;
int member_count, insert_count, delete_count;
int member_count_per_thread, insert_count_per_thread, delete_count_per_thread;
struct list_node_s *head_p;
pthread_mutex_t list_mutex;

void *RandomTaskHandler(void *rank);
int16_t RandomIntegerGenerator();
void DisplayStatistics(const char* label, int count, int countPerThread);

struct list_node_s
{
    int data;
    struct list_node_s *next;
};

int main(int argc, char *argv[])
{
    long thread;
    pthread_t *thread_handles;
    clock_t start_time, end_time;
    double cpu_time_used;

    pthread_mutex_init(&list_mutex, NULL);

    srand(time(NULL));

    thread_count = strtol(argv[1], NULL, 10);
    n = strtol(argv[2], NULL, 10);
    m = strtol(argv[3], NULL, 10);
    m_member = strtod(argv[4], NULL);
    m_insert = strtod(argv[5], NULL);
    m_delete = strtod(argv[6], NULL);

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

    pthread_mutex_destroy(&list_mutex);

    return 0;
}



int Member(int value, struct list_node_s **head_p)
{
    struct list_node_s *curr_p = *head_p;

    while (curr_p != NULL && curr_p->data < value)
    {
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Insert(int value, struct list_node_s **head_pp)
{
    struct list_node_s *curr_p = *head_pp;
    struct list_node_s *pred_p = NULL;
    struct list_node_s *temp_p;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL)
        {
            *head_pp = temp_p;
        }
        else
        {
            pred_p->next = temp_p;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int Delete(int value, struct list_node_s **head_pp)
{
    struct list_node_s *curr_p = *head_pp;
    struct list_node_s *pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value)
    {
        if (pred_p == NULL)
        {
            *head_pp = curr_p->next;
        }
        else
        {
            pred_p->next = curr_p->next;
        }
        free(curr_p);
        return 1;
    }
    else
    {
        return 0;
    }
}

void Populate(struct list_node_s *head_p, int n)
{
    int i = 0;

    while (i < n - 1)
    {
        int16_t value = RandomIntegerGenerator();
        if (Member(value, &head_p))
        {
            continue;
        }
        Insert(value, &head_p);
        i++;
    }
}

void Display(struct list_node_s *head_p)
{
    struct list_node_s *curr_p = head_p;
    int i = 0;
    while (curr_p != NULL)
    {
        printf("Node %d: %d\n", i, curr_p->data);
        i++;
        curr_p = curr_p->next;
    }
}

void DisplayStatistics(const char *label, int count, int countPerThread)
{
    printf("%s:\n", label);
    printf("Total: %d\n", count);
    printf("Per Thread: %d\n", countPerThread);
}

int16_t RandomIntegerGenerator()
{
    int16_t max_value = __INT16_MAX__;
    int16_t value = rand() % (max_value + 1);
    return value;
}

void *RandomTaskHandler(void *rank)
{
    long my_rank = (long)rank;

    int (*functions[])() = {Member, Insert, Delete};
    int counts[] = {0, 0, 0};
    int counts_per_thread[] = {member_count_per_thread, insert_count_per_thread, delete_count_per_thread};

    int totalCalls = member_count_per_thread + insert_count_per_thread + delete_count_per_thread;
    int remainingCalls = totalCalls;

    while (remainingCalls > 0)
    {
        int randomIndex = rand() % 3;

        if (counts[randomIndex] < counts_per_thread[randomIndex])
        {
            pthread_mutex_lock(&list_mutex);
            functions[randomIndex](RandomIntegerGenerator(), &head_p);
            pthread_mutex_unlock(&list_mutex);
            counts[randomIndex]++;
            remainingCalls--;
        }
    }

    return NULL;
}
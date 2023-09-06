#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedList.h"

int thread_count;
int n;
int16_t m;
float m_member, m_insert, m_delete;


int main(int argc, char* argv[]){
    long thread;
    pthread_t* thread_handles;
    clock_t start_time, end_time;
    double cpu_time_used;

    srand(time(NULL));

    n = strtol(argv[1], NULL, 10);
    m = strtol(argv[2], NULL, 10);
    m_member = strtod(argv[3], NULL);
    m_insert = strtod(argv[4], NULL);
    m_delete = strtod(argv[5], NULL);

    int num_member = m*m_member;
    int num_insert = m*m_insert;
    int num_delete = m*m_delete;

    struct list_node_s* head_p = malloc(sizeof(struct list_node_s));
    Populate(head_p, n);

    start_time = clock();

    for (int i=0; i<num_member; i++){
        Member(RandomIntegerGenerator(), &head_p);
    }

    for (int i=0; i<num_insert; i++){
        Insert(RandomIntegerGenerator(), &head_p);
    }

    for (int i=0; i<num_delete; i++){
        Delete(RandomIntegerGenerator(), &head_p);
    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf(" Start to End Duration (CPU): %f s\n", cpu_time_used);

    return 0;
}

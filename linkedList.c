#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedList.h"

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

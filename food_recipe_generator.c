#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

typedef struct elements
{
    char ele[50];
} node;

typedef struct queue
{
    int val;
    struct queue *next;
} queue;

queue *enqueue(queue *head, int value)
{
    if (head == NULL)
    {
        head = malloc(sizeof(queue));
        head->val = value;
        head->next = NULL;
        return head;
    }

    queue *tmp = head;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = malloc(sizeof(queue));
    tmp->next->val = value;
    tmp->next->next = NULL;
    return head;
}

queue *dequeue(queue *head) 
{
    if (head == NULL)
    {
        return NULL;
    }

    head = head->next;
    return head;
}


void init_all(int num, int visi[num], int ad_mat[num][num])
{
    for (int i = 0; i < num; i++)
    {
        visi[i] = 0;
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            ad_mat[i][j] = 0;
        }
    }
}

int map_ele(int num, node arr[num], char target[50])
{
    int flag;

    for (int i = 0; i < num; i++)
    {
        if (strcmp(target, arr[i].ele) == 0)
        {
            flag = i;
            break;
        }
    }

    return flag;
}

void display_map(int num, node arr[num])
{
    int count = 0;
    printf("\n");

    for (int i = 0; i < num; i++)
    {
        count++;
        printf("%s -> %d  ", arr[i].ele, map_ele(num, arr, arr[i].ele));
        if (count == 3)
        {
            count = 0;
            printf("\n");
        }
    }

    // printf("\n");
}

void cns_graph(int num, node arr[num], int ad_mat[num][num])
{
    int edge, temp1, temp2;

    for (int i = 0; i < num; i++)
    {
        printf("\nEnter element %d = ", i + 1);
        scanf(" %[^\n]s", &arr[i].ele);
        // fgets(arr[i].ele, 50, stdin);
    }

    printf("\nEnter the number of edge = ");
    scanf("%d", &edge);

    display_map(num, arr);

    for (int i = 0; i < edge; i++)
    {
        printf("\nEnter elements of Edge %d = ", i + 1);
        scanf("%d %d", &temp1, &temp2);

        ad_mat[temp1][temp2] = 1;
    }
}

void calc_in_deg(int num, int ad_mat[num][num], int in_deg[num])
{
    int count = 0;
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<num; j++)
        {
            if(ad_mat[j][i] == 1)
            {
                count++;
            }
        }
        in_deg[i] = count;
        count = 0;
    }
}

void topo_sort(int num, node arr[num], int ad_mat[num][num], int visi[num], int in_deg[num], queue *head)
{
    printf("\n");

    for(int i=0; i<num; i++)
    {
        if(in_deg[i] == 0)
        {
            head = enqueue(head, i);
            visi[i] = 1;
        }
    }

    while(head != NULL)
    {
        for(int i=0; i<num; i++)
        {
            if(ad_mat[head->val][i] == 1)
            {
                if(visi[i] != 1)
                {
                    in_deg[i] -= 1;
                    if(in_deg[i] == 0)
                    {
                        head = enqueue(head, i);
                        visi[i] = 1;
                    }
                }
            }
        }

        printf("%s\n", arr[head->val].ele);
        head = dequeue(head);
    }
}

int main()
{
    int num, edge;

    printf("\nEnter the number of elements = ");
    scanf("%d", &num);

    node arr[num];
    int ad_mat[num][num], visi[num], in_deg[num];
    queue *head = NULL;

    cns_graph(num, arr, ad_mat);

    topo_sort(num, arr, ad_mat, visi, in_deg, head);

    printf("\n::::PROGRAM EXITED::::\n\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct recipe
{
    char recipe_ele[50];
    struct recipe *dir1;
    struct recipe *dir2;
} node;

typedef struct mapper
{
    char element[50];
    int val;
    struct mapper *next;
} map;

node *cns_reci_list(node *start)
{

}

node *topo_sort(node *start)
{
    
}

void display_reci(node *start)
{

}

void display_map(map *head)
{
    while (head != NULL)
    {
        printf("\nElement = %s", head->element);
        printf("\nValue = %d", head->val);
        head = head->next;
    }
}

int main()
{
    int reci_ele, reci_steps, s1, s2;
    printf("\nEnter the number of recipe elements = ");
    scanf("%d", &reci_ele);
    printf("\nEnter the number of recipe steps = ");
    scanf("%d", &reci_steps);

    int ad_mat[reci_ele][reci_steps];
    char ele[50];

    map *head = NULL;
    map *trav = NULL;
    map *tmp = NULL;

    for (int i = 0; i < reci_ele; i++)
    {
        printf("\nEnter the recipe element %d", i + 1);
        fgets(ele, 50, stdin);

        if (i == 0)
        {
            tmp = malloc(sizeof(map));
            strcpy(tmp->element, ele);
            tmp->val = i + 1;
            head = tmp;
            trav = tmp;
        }
        else
        {
            tmp = malloc(sizeof(map));
            strcpy(tmp->element, ele);
            tmp->val = i + 1;
            trav->next = tmp;
            trav = trav->next;
        }
    }

    trav->next = NULL;

    for (int i = 0; i < reci_ele; i++)
    {
        for (int j = 0; j < reci_steps; j++)
        {
            ad_mat[i][j] = 0;
        }
    }

    for (int i = 0; i < reci_steps; i++)
    {
        printf("\nEnter the step %d = ", i + 1);
        scanf("%d %d", &s1, &s2);
        ad_mat[s1 - 1][s2 - 1] = 1;
    }

    return 0;
}
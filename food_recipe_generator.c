#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <conio.h>

typedef struct elements
{
    char ele[50];
} node;

typedef struct queue
{
    int val;
    struct queue *next;
} queue;

typedef struct usr
{
    char f_name[25];
    char u_name[25];
    char e_mail[30];
    char mob[13];
    char pwd[25];
} usr;

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

void init_all(int num, int visited[num], int ad_mat[num][num])
{
    for (int i = 0; i < num; i++)
    {
        visited[i] = 0;
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
    printf("\n\t\t");

    for (int i = 0; i < num; i++)
    {
        count++;
        printf("%s -> %d  ", arr[i].ele, map_ele(num, arr, arr[i].ele));
        if (count == 3)
        {
            count = 0;
            printf("\n\t\t");
        }
    }

    // printf("\n");
}

void cns_graph(int num, node arr[num], int ad_mat[num][num])
{
    int edge, temp1, temp2;

    for (int i = 0; i < num; i++)
    {
        printf("\n\t\tEnter element %d = ", i + 1);
        scanf(" %[^\n]s", &arr[i].ele);
        // fgets(arr[i].ele, 50, stdin);
         
    }

    printf("\n\t\tEnter the number of edge = ");
    scanf("%d", &edge);

    display_map(num, arr);

    for (int i = 0; i < edge; i++)
    {
        printf("\n\t\tEnter elements of Edge %d = ", i + 1);
        scanf("%d %d", &temp1, &temp2);

        ad_mat[temp1][temp2] = 1;
    }
}

void calc_in_deg(int num, int ad_mat[num][num], int in_deg[num])
{
    int count = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (ad_mat[j][i] == 1)
            {
                count++;
            }
        }
        in_deg[i] = count;
        count = 0;
    }
}

void topo_sort(int num, node arr[num], int ad_mat[num][num], int visited[num], int in_deg[num], queue *head)
{
    int pop_ele, time = 0;
    printf("\n");

    for (int i = 0; i < num; i++)
    {
        if (in_deg[i] == 0)
        {
            head = enqueue(head, i);
        }
    }

    while (head != NULL)
    {
        if (visited[head->val] != 1)
        {
            if (time == 0)
            {
                printf("\t\t%s\n", arr[head->val].ele);
                usleep(1000000);
                visited[head->val] = 1;
                time = 1;
            }
            else
            {
                printf("\n\t\t  %c\n", 25);
                printf("\t\t%s\n", arr[head->val].ele);
                usleep(1000000);
                visited[head->val] = 1;
            }
        }
        pop_ele = head->val;
        head = dequeue(head);

        for (int i = 0; i < num; i++)
        {
            if (ad_mat[pop_ele][i] == 1)
            {
                if (visited[i] != 1 && in_deg[i] != 0)
                {
                    in_deg[i] -= 1;
                    if (in_deg[i] == 0)
                    {
                        head = enqueue(head, i);
                        printf("\n\t\t  %c\n", 25);
                        printf("\t\t%s\n", arr[i].ele);
                        usleep(1000000);
                        visited[i] = 1;
                    }
                }
            }
        }
    }
}

// void box(int a, int b, int c, int d)
// {
//     for(int i=a; i<c; i++)
//     {
//         gotoxy(i,b);
//         printf("\xcd");
//         gotoxy(i,d);
//         printf("\xcd");
//     }

//     for(int j=b; j<d; j++)
//     {
//         gotoxy(a,j);
//         printf("\xba");
//         gotoxy(c,j);
//         printf("\xba");
//     }
//     gotoxy(a,b);
//     printf("\xc9");
//     gotoxy(c,b);
//     printf("\xbb");
//     gotoxy(a,d);
//     printf("\xc8");
//     gotoxy(c,d);
//     printf("\xbc");

// }

void print_title()
{
    system("cls");
    printf("\n\n");
    system("color 0E");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\t\t\t\t\t\tFOOD RECIPE GENERATOR\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
}

void thank_you()
{
    printf("\n\n");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\t\t\t\t\t\t::::THANK YOU::::\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
}

void pwd_gen()
{
    int i = 0;
    char ch;
    char usr[25];
    char pwd[25];
    printf("\n\n\t\tEnter Username = ");
    scanf("%s", usr);
    printf("\n\t\tEnter Password = ");
    while ((ch = _getch()) != 13)
    {
        pwd[i] = ch;
        printf("*");
        i++;
    }
    pwd[i] = '\0';
}

void login_pg()
{
    system("cls");
    printf("\n\n");
    system("color 0E");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\t\t\t\t\t\tLOGIN PAGE\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    int choice;

    printf("\n\n\t\t1.Sign Up");
    printf("\n\t\t2.Sign In");
    printf("\n\t\t3.Exit");

    printf("\n\t\tEnter your choice = ");
    scanf("%d", &choice);

    while (choice != 3)
    {
        if (choice == 1)
        {
            sign_up();
        }
        else if (choice == 2)
        {
            sign_in();
        }

        printf("\n\t\tEnter your choice = ");
        scanf("%d", &choice);
    }
}

void sign_in()
{
    system("cls");
    printf("\n\n");
    system("color 0E");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\t\t\t\t\t\tSIGN IN PAGE\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    char tmp1[25], tmp2[25];

    printf("\n\n\t\tEnter your username = ");
    scanf("%s", tmp1);
    printf("\n\t\tEnter your password = ");

    int i = 0;
    char ch;

    while ((ch = _getch()) != 13)
    {
        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        tmp2[i] = ch;
        printf("*");
        i++;
    }
    tmp2[i] = '\0';
}

void sign_up()
{
    usr user;
    char ch, ch2, c_pwd[25];
    int i = 0;

    system("cls");
    printf("\n\n");
    system("color 0E");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\t\t\t\t\t\tSIGN UP PAGE\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    printf("\n\n\t\tEnter your Full name = ");
    scanf(" %[^\n]s", user.f_name);
    printf("\n\t\tSet an username = ");
    scanf(" %s", user.u_name);
    printf("\n\t\tEnter your mobile number = ");
    scanf(" %s", user.mob);
    printf("\n\t\tEnter your email id = ");
    scanf(" %s", user.e_mail);
    printf("\n\t\tSet an password = ");
    while ((ch = _getch()) != 13)
    {
        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        user.pwd[i] = ch;
        printf("*");
        i++;
    }
    user.pwd[i] = '\0';

    i = 0;

    printf("\n\t\tConfirm your password = ");
    while ((ch2 = _getch()) != 13)
    {
        if (ch2 == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        c_pwd[i] = ch2;
        printf("*");
        i++;
    }
    c_pwd[i] = '\0';

    if (strcmp(c_pwd, user.pwd) != 0)
    {
        printf("\n\n\t\tPassword doesn't match");
        Beep(750, 300);
    }
}

void design()
{
    printf("\n\n");
    system("color 0E");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
}

int main()
{
    int num, edge;

    printf("\n::::PROGRAM STARTED::::\n\n");

    login_pg();

    print_title();

    pwd_gen();

    printf("\n\n\t\tEnter the number of elements = ");
    scanf("%d", &num);

    node arr[num];
    int ad_mat[num][num], visited[num], in_deg[num];
    queue *head = NULL;

    cns_graph(num, arr, ad_mat);

    calc_in_deg(num, ad_mat, in_deg);

    topo_sort(num, arr, ad_mat, visited, in_deg, head);

    // printf("\n\t\t\t::::PROGRAM EXITED::::\n\n");

    thank_you();

    return 0;
}
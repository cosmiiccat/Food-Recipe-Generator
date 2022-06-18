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
// #include <graphics.h>

#define VAL 9999888

FILE *fptr;
FILE *fptr2;

typedef struct elements
{
    char ele[100];
} node;

typedef struct queue
{
    int val;
    struct queue *next;
} queue;

typedef struct usr
{
    char f_name[100];
    char u_name[100];
    char e_mail[100];
    char mob[100];
    char pwd[100];
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

int map_ele(int num, node arr[num], char target[100])
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

void topo_sort(int num, node arr[num], int ad_mat[num][num], int visited[num], int in_deg[num], queue *head, node *reci_name)
{
    int pop_ele, time = 0;
    printf("\n");

    fptr2 = fopen("contents.txt", "r");
    char ch;
    int counter = 0;
    while (1)
    {
        ch = fgetc(fptr2);
        if (ch == EOF)
            break;
        if (ch == '\n')
            counter++;
    }
    fclose(fptr2);

    char recipe_file_name[] = "recipe";
    char txt[] = "0.txt";
    txt[0] = counter + 49;
    strcat(recipe_file_name, txt);

    fptr = fopen(recipe_file_name, "w+");

    fptr2 = fopen("contents.txt", "a");

    fprintf(fptr2, "%s\n", reci_name->ele);

    fprintf(fptr, "%d\n", num);

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
                // printf("\t\t%s\n", arr[head->val].ele);
                // usleep(1000000);
                fprintf(fptr, "%s\n", arr[head->val].ele);
                visited[head->val] = 1;
                time = 1;
            }
            else
            {
                // printf("\n\t\t  %c\n", 25);
                // printf("\t\t%s\n", arr[head->val].ele);
                // usleep(1000000);
                fprintf(fptr, "%s\n", arr[head->val].ele);
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
                        // printf("\n\t\t  %c\n", 25);
                        // printf("\t\t%s\n", arr[i].ele);
                        // usleep(1000000);
                        fprintf(fptr, "%s\n", arr[i].ele);
                        visited[i] = 1;
                    }
                }
            }
        }
    }
    fclose(fptr);
    fclose(fptr2);
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

void display_recipe()
{
    fptr2 = fopen("contents.txt", "r");

    char choice;
    char ch;
    char recipe_name[100];
    int counter = 0, index = 1;

    while (true)
    {
        ch = fgetc(fptr2);
        if (ch == EOF)
            break;
        if (ch == '\n')
            counter++;
    }
    fseek(fptr2, 0, SEEK_SET);

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

    printf("\n");

    while (counter--)
    {
        fgets(recipe_name, sizeof(recipe_name), fptr2);
        printf("\t\tEnter %d ----> %s\n", index++, recipe_name);
    }

    printf("Enter your choice : ");
    scanf(" %c", &choice);

    char recipe_file_name[] = "recipe";
    char txt[] = "0.txt";
    txt[0] = choice;
    strcat(recipe_file_name, txt);

    fptr = fopen(recipe_file_name, "r");
    int steps_num;
    char step[200];
    fgets(step, sizeof(step), fptr);
    steps_num = atoi(step);
    // printf("\n%d\n", steps_num);
    for (int i = 0; i < steps_num; i++)
    {
        if (i != 0)
        {
            printf("\n\t\t  %c\n", 25);
        }
        fgets(step, sizeof(step), fptr);
        printf("\t\t %s\n", step);
        usleep(1000000);
    }
    fclose(fptr);

    getch();
}

void print_title()
{
    // system("cls");
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

void iiit_kalyani()
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
    printf("\n\t\t\t\t\t\tIIIT KALYANI\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
}

void dsa_project()
{
    // system("cls");
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
    printf("\n\t\t\t\t\t\tDSA PROJECT\n");
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
    char usr[100];
    char pwd[100];
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

void hashing(int size, char arr[size], char hash[1000])
{
    int size2 = size;
    size = 1000;

    srand(time(0));

    int r, count = 0, track = 0, count2 = 0;

    // char hash[1000], temp[100];

    for (int i = 0; i < 1000; i++)
    {
        // if (count < size2 && arr[i] != '\0' && arr[i] != '\n' && track == 0)
        // {
        //     if (i == 5 + (5 * count))
        //     {
        //         hash[i] = arr[i];
        //         count++;
        //     }

        //     if (arr[i] != '\0' && arr[i] != '\n')
        //     {
        //         track = 1;
        //     }
        // }
        // else
        // {
        // }
        r = rand();
        r = r % 50;
        r += 49;

        hash[i] = r;
        // printf("%c ", hash[i]);
    }

    for(int i=0; i<100; i++)
    {
        if(arr[i] == '\0' || arr[i] == '\n')
        {
            break;
        }
        track = 5*i + 5;
        hash[track] = arr[i];
        count2++; 
    }

    hash[0] = count2;
    // printf("%s", hash);

    // return hash;
    // getch();
}

// bool hash_check(int arr[100])
// {
//     int hash_p[1000];

//     fptr = fopen()
// }

bool sign_up()
{
    usr user;
    char ch, ch2, c_pwd[100];
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

    fptr = fopen("details.txt", "w");

    printf("\n\n\t\tEnter your Full name = ");
    scanf(" %[^\n]s", user.f_name);
    fprintf(fptr, "%s\n", user.f_name);
    printf("\n\t\tSet an username = ");
    scanf(" %s", user.u_name);
    fprintf(fptr, "%s\n", user.u_name);
    printf("\n\t\tEnter your mobile number = ");
    scanf(" %s", user.mob);
    fprintf(fptr, "%s\n", user.mob);
    printf("\n\t\tEnter your email id = ");
    scanf(" %s", user.e_mail);
    fprintf(fptr, "%s\n", user.e_mail);
    fclose(fptr);
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

    printf("\n\n\t\tConfirm your password = ");
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
        fptr = fopen("details.txt", "w");
        fclose(fptr);
        return false;
    }
    else
    {
        fptr = fopen("password.txt", "w");
        // char *f_ptr;
        char f_pwd[1000];
        hashing(100, user.pwd, f_pwd);
        // printf("\n---------%s---------\n", f_pwd);
        // strncpy(f_pwd, f_ptr, 1000);
        fprintf(fptr, "%s\n", f_pwd);
        fclose(fptr);
        return true;
        // fprintf(fptr, "%s\n", user.pwd);
    }
}

bool sign_in()
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

    char tmp1[100], tmp2[100];

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

    char temp1[100], temp2[1000];

    fptr = fopen("details.txt", "r");
    fptr2 = fopen("password.txt", "r");

    for (int i = 0; i < 2; i++)
    {
        fgets(temp1, sizeof(temp1), fptr);
    }

    fgets(temp2, sizeof(temp2), fptr2);

    fclose(fptr);
    fclose(fptr2);

    for (int i = 0; i < 100; i++)
    {
        if (temp1[i] == '\n')
        {
            temp1[i] = '\0';
        }

        if (temp2[i] == '\n')
        {
            temp2[i] = '\0';
        }
    }

    int check = 0;

    // printf("%d", temp2[0]);
    // usleep(10000000);

    for(int i=0; i<temp2[0]; i++)
    {
        // if(tmp2[i] == '\0' || tmp2[i] == '\n')
        // {
        //     break;
        // }

        if(tmp2[i] != temp2[5*i + 5])
        {
            check = 1;
        }
    }

    if (strcmp(temp1, tmp1) == 0 && check == 0)
    {
        return true;
    }

    return false;
}

int login_pg()
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

    int choice, flag;
    bool s1, s2;

    printf("\n\n\t\t1.Sign Up");
    printf("\n\t\t2.Sign In");
    printf("\n\t\t3.Exit");

    printf("\n\n\t\tEnter your choice = ");
    scanf("%d", &choice);

    if (choice == 3)
    {
        flag = 3;
    }

    while (choice != 3 && choice != 0)
    {
        if (choice == 1)
        {
            s1 = sign_up();
            if (s1 == true)
            {
                choice = 2;
            }
            else
            {
                Beep(750, 300);
                flag = VAL;
                break;
            }
        }
        else if (choice == 2)
        {
            s2 = sign_in();

            if (s2 == true)
            {
                flag = 0;
                break;
            }
            else
            {
                Beep(750, 300);
                flag = VAL;
                break;
            }
        }
    }

    return flag;
}

int main_menu()
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
    printf("\n\t\t\t\t\t\tMAIN MENU\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    int choice, flag;

    printf("\n\n\t\t1.Add New Recipe");
    printf("\n\t\t2.View Recipe(s)");
    printf("\n\t\t3.Exit");

    printf("\n\n\t\tEnter your choice = ");
    scanf("%d", &choice);

    if (choice == 3)
    {
        flag = 3;
    }
    if (choice == 1)
    {
        flag = 1;
    }
    else if (choice == 2)
    {
        // display_recipe;
        flag = 2;
    }

    return flag;
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
    int num, edge, status = VAL, status2 = VAL;

    // getch();

    // printf("\n::::PROGRAM STARTED::::\n\n");
    iiit_kalyani();
    print_title();
    dsa_project();

    printf("\n\n");

    getch();

    while (status == VAL)
    {
        status = login_pg();
    }

    if (status == 0)
    {
        while (status2 != 3)
        {
            status2 = main_menu();

            if (status2 == 1)
            {
                node reci_name;

                printf("\n\n\t\tEnter recipe name = ");
                scanf(" %[^\n]s", reci_name.ele);

                printf("\n\t\tEnter the number of elements = ");
                scanf("%d", &num);

                node arr[num];
                int ad_mat[num][num], visited[num], in_deg[num];
                queue *head = NULL;

                cns_graph(num, arr, ad_mat);

                calc_in_deg(num, ad_mat, in_deg);

                topo_sort(num, arr, ad_mat, visited, in_deg, head, &(reci_name));
            }
            else if (status2 == 2)
            {
                display_recipe();
            }
        }
    }

    // login_pg();

    // print_title();

    // pwd_gen();

    // node reci_name;

    // printf("\n\n\t\tEnter recipe name = ");
    // scanf("%[^\n]s", reci_name.ele);

    // printf("\n\t\tEnter the number of elements = ");
    // scanf("%d", &num);

    // node arr[num];
    // int ad_mat[num][num], visited[num], in_deg[num];
    // queue *head = NULL;

    // cns_graph(num, arr, ad_mat);

    // calc_in_deg(num, ad_mat, in_deg);

    // topo_sort(num, arr, ad_mat, visited, in_deg, head, &(reci_name));

    // display_recipe();

    // // printf("\n\t\t\t::::PROGRAM EXITED::::\n\n");

    thank_you();

    printf("\n");

    return 0;
}
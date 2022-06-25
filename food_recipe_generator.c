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
FILE *fptr3;

typedef struct elements
{
    char ele[100];
} node;

typedef struct queue
{
    int val;
    struct queue *next;
} queue;

typedef struct stack
{
    char p;
    struct stack *to;
} stack;

typedef struct tree
{
    int val;
    struct tree *left;
    struct tree *right;
} tree;

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

stack *push(stack *top, char ch)
{
    if (top == NULL)
    {
        top = malloc(sizeof(stack));
        top->p = ch;
        top->to = NULL;
        return top;
    }

    stack *tmp = malloc(sizeof(stack));
    tmp->p = ch;
    tmp->to = top;
    top = tmp;

    return top;
}

stack *pop(stack *top)
{
    if (top != NULL)
    {
        top = top->to;
        return top;
    }
    else
    {
        return NULL;
    }
}

void design()
{
    printf("\n\n");
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
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

    printf("\n\t\tRECIPE NAME: \"%s\"\n\n", reci_name->ele);

    while (head != NULL)
    {
        if (visited[head->val] != 1)
        {
            if (time == 0)
            {
                printf("\t\t\t\t\t%s", arr[head->val].ele);
                usleep(1000000);
                fprintf(fptr, "%s\n", arr[head->val].ele);
                visited[head->val] = 1;
                time = 1;
            }
            else
            {
                printf("\n\t\t\t\t\t  %c\n", 25);
                printf("\t\t\t\t\t%s", arr[head->val].ele);
                usleep(1000000);
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
                        printf("\n\t\t\t\t\t  %c\n", 25);
                        printf("\t\t\t\t\t%s", arr[i].ele);
                        usleep(1000000);
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

void heapify_max(int *arr, int size)
{
    int temp;
    for (int j = (size / 2) - 1; j >= 0; j--)
    {

        int i = j;
        int check = 0;
        while (2 * i + 1 < size)
        {
            if (2 * i + 2 == size)
            {
                if (*(arr + i) < *(arr + 2 * i + 1))
                {
                    temp = *(arr + i);
                    *(arr + i) = *(arr + 2 * i + 1);
                    *(arr + 2 * i + 1) = temp;
                    i = 2 * i + 1;
                    check = 1;
                }
            }
            else
            {
                if (*(arr + 2 * i + 2) > *(arr + 2 * i + 1))
                {
                    if (*(arr + i) < *(arr + 2 * i + 2))
                    {
                        temp = *(arr + i);
                        *(arr + i) = *(arr + 2 * i + 2);
                        *(arr + 2 * i + 2) = temp;
                        i = 2 * i + 2;
                        check = 1;
                    }
                }
                else
                {
                    if (*(arr + i) < *(arr + 2 * i + 1))
                    {
                        temp = *(arr + i);
                        *(arr + i) = *(arr + 2 * i + 1);
                        *(arr + 2 * i + 1) = temp;
                        i = 2 * i + 1;
                        check = 1;
                    }
                }
            }

            if (check == 1)
            {
                check = 0;
            }
            else
            {
                break;
            }
            // printf("\nDEBUG %d %d\n", size, i);
        }
    }
}

tree *lvl_order(int *arr, tree *root, int idx, int size)
{
    if (idx < size)
    {
        root = malloc(sizeof(node));
        root->val = *(arr + idx);
        root->left = NULL;
        root->right = NULL;

        root->left = lvl_order(arr, root->left, 2 * idx + 1, size);
        root->right = lvl_order(arr, root->right, 2 * idx + 2, size);
    }
    return root;
}

tree *pop_max(tree *root)
{
    // printf("\npop_%d_%d_%d\n", root->val, root->left->val, root->right->val);

    if (root == NULL)
    {
        return NULL;
    }
    tree *p = root;
    tree *q = root;
    int temp;

    if (p->left == NULL && p->right == NULL)
    {
        return NULL;
    }
    // printf("\nDEBUG A1\n");
    // printf("\npop_%d_%d_%d\n", root->val, root->left->val, root->right->val);
    // printf("\npop_p_%d_%d_%d\n", p->val, p->left->val, p->right->val);

    // printf("\n%d___%d\n", p->left->val, p->right->val);
    while (true)
    {
        if (p->left == NULL)
        {
            // printf("\nDEBUG A2\n");

            p = p->right;
            temp = p->val;
            p->val = q->val;
            q->val = temp;
            if (p->left == NULL && p->right == NULL)
            {
                q->right = NULL;
                break;
            }
            q = p;
        }

        if (p->right == NULL)
        {
            // printf("\nDEBUG A3\n");

            p = p->left;
            temp = p->val;
            p->val = q->val;
            q->val = temp;
            if (p->left == NULL && p->right == NULL)
            {
                q->left = NULL;
                break;
            }
            q = p;
        }
        // printf("\nCHECK 01\n");
        // printf("\n%d___%d\n", p->left->val, p->right->val);

        if (p->left != NULL && p->right != NULL)
        {
            if (p->left->val > p->right->val)
            {
                // printf("\nDEBUG A4\n");

                p = p->left;
                temp = p->val;
                p->val = q->val;
                q->val = temp;
                if (p->left == NULL && p->right == NULL)
                {
                    q->left = NULL;
                    break;
                }
                q = p;
            }
            else
            {
                // printf("\nDEBUG A5\n");

                p = p->right;
                temp = p->val;
                p->val = q->val;
                q->val = temp;
                if (p->left == NULL && p->right == NULL)
                {
                    q->right = NULL;
                    break;
                }
                q = p;
            }
        }
    }
    return root;
}

tree *del_max(tree *root, int size, int *arr)
{

    for (int i = 0; i < size; i++)
    {
        // printf("\ndel_%d_%d_%d\n", root->val, root->left->val, root->right->val);

        // printf("\nDEBUG A\n");
        // printf("\n%d\n", *(arr + i));
        *(arr + i) = root->val;
        // printf("\nDEBUG B\n");

        root = pop_max(root);
    }
    return root;
}

void recom_reci()
{
    int freq[10], freq2[10];
    char tmp_str[3], ch, reci_name[100];
    int count = 0, reci_no, cur = 2, k = 0, flag;

    for (int i = 0; i < 10; i++)
    {
        freq[i] = 0;
        freq2[i] = 0;
    }

    fptr = fopen("history.txt", "r");

    // printf("\n");
    design();
    // printf("\n");

    printf("\n\n\t\t\t\t   :::: RECOMMENDED RECIPES ::::\n");

    if (fptr == NULL)
    {
        printf("\n\t\tYou don't have any previously saved history\n");
    }
    else
    {
        while (true)
        {
            ch = fgetc(fptr);
            if (ch == EOF)
                break;
            if (ch == '\n')
                count++;
        }
        fseek(fptr, 0, SEEK_SET);

        while (count--)
        {
            fgets(tmp_str, sizeof(tmp_str), fptr);
            reci_no = atoi(tmp_str);
            freq[reci_no] = freq[reci_no] + 1;
            freq2[reci_no] = freq2[reci_no] + 1;
        }

        fclose(fptr);

        tree *root = NULL;

        heapify_max(freq, 10);

        root = lvl_order(freq, root, 0, 10);

        root = del_max(root, 10, freq);

        fptr = fopen("contents.txt", "r");

        while (cur--)
        {
            for (int i = 0; i < 10; i++)
            {
                if (freq2[i] == freq[k])
                {
                    flag = i;
                    // printf("\n%d %d\n", flag, k);
                    while (flag--)
                    {
                        fgets(reci_name, sizeof(reci_name), fptr);
                    }
                    fseek(fptr, 0, SEEK_SET);

                    printf("\n\t\t %s\n", reci_name);

                    i = 0;
                    k++;
                    break;
                }
            }
        }
    }

    fclose(fptr);
}

void view_profile()
{
    fptr = fopen("details.txt", "r");

    system("cls");
    printf("\n\n");
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t    VIEW PROFILE\n\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    int count = 0;
    char ch, detail[100];

    while (true)
    {
        ch = fgetc(fptr);
        if (ch == EOF)
            break;
        if (ch == '\n')
            count++;
    }
    fseek(fptr, 0, SEEK_SET);

    fgets(detail, sizeof(detail), fptr);

    printf("\n\n\t\tNAME : %s\n", detail);

    fgets(detail, sizeof(detail), fptr);

    printf("\t\tUSERNAME : %s\n", detail);

    fgets(detail, sizeof(detail), fptr);

    printf("\t\tPHONE NUMBER : %s\n", detail);

    fgets(detail, sizeof(detail), fptr);

    printf("\t\tEMAIL ID : %s\n", detail);
}

void display_recipe()
{
    fptr2 = fopen("contents.txt", "r");
    fptr3 = fopen("history.txt", "r");

    char choice;
    char ch;
    char recipe_name[100];
    int counter = 0, index = 1, counter2 = 0, flag2;
    char reci_num, reci_name[100];
    int reci_no, ichoice, flag;

    char tmp_str[3];
    // tmp_str[1] = '\0';

    queue *hist = NULL;
    stack *top = NULL;

    while (true)
    {
        ch = fgetc(fptr2);
        if (ch == EOF)
            break;
        if (ch == '\n')
            counter++;
    }
    fseek(fptr2, 0, SEEK_SET);

    if (fptr3 == NULL)
    {
        counter2 = 0;
    }
    else
    {
        while (true)
        {
            ch = fgetc(fptr3);
            if (ch == EOF)
                break;
            if (ch == '\n')
                counter2++;
        }
        fseek(fptr3, 0, SEEK_SET);

        flag = counter2;

        // printf("%d****", counter2);

        while (counter2--)
        {
            fgets(tmp_str, sizeof(tmp_str), fptr3);
            reci_no = atoi(tmp_str);
            // printf("\n----%s %d---\n", tmp_str, reci_no);
            hist = enqueue(hist, reci_no);
        }
    }

    // getch();

    system("cls");
    printf("\n\n");
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t        CONTENTS\n\n");
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
        printf("\n\t\t\t\t%d. %s", index++, recipe_name);
    }

    printf("\n");

    recom_reci();

    // printf("\n");
    design();
    printf("\n");

    printf("\n");

    printf("\t\tEnter your choice : ");
    scanf(" %c", &choice);

    flag2 = (int)choice - 48;

    tmp_str[0] = choice;
    tmp_str[1] = '\0';

    ichoice = atoi(tmp_str);

    // printf("\n");

    // printf("\nDEBUG 01\n");

    if (flag == 10)
    {
        // hist = dequeue(hist);
        queue *temp = hist;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NULL;
        // hist = enqueue(hist, ichoice);
        queue *tmp = malloc(sizeof(queue));
        tmp->val = ichoice;
        tmp->next = hist;
        hist = tmp;
    }
    else
    {
        // hist = enqueue(hist, ichoice);
        queue *tmp = malloc(sizeof(queue));
        tmp->val = ichoice;
        tmp->next = hist;
        hist = tmp;
    }

    // printf("\nDEBUG 02\n");
    // printf("\n%d %d\n", hist->val, hist->next->val);
    fclose(fptr3);

    fptr3 = fopen("history.txt", "w");

    while (hist != NULL)
    {
        reci_no = hist->val;
        hist = dequeue(hist);
        reci_num = (char)(reci_no + 48);
        tmp_str[0] = reci_num;
        tmp_str[1] = '\0';
        fprintf(fptr3, "%s\n", tmp_str);
        // top = push(top, reci_num);

        // printf("\nA\n");
    }

    // printf("\nDEBUG 02A\n");

    fclose(fptr3);

    fptr3 = fopen("contents.txt", "r");

    while (flag2--)
    {
        fgets(reci_name, sizeof(reci_name), fptr3);
    }

    fclose(fptr3);

    printf("\n\t\tRECIPE NAME: \"%s\"\n\n", reci_name);

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
            printf("\t\t  %c", 25);
        }
        fgets(step, sizeof(step), fptr);
        printf("\n\t\t %s", step);
        usleep(1000000);
    }
    fclose(fptr);

    // getch();
}

void view_history()
{
    int counter = 0, reci_no, temp;
    char ch, reci_num;
    char reci_name[100];
    char tmp_str[3];

    fptr = fopen("history.txt", "r");
    fptr2 = fopen("contents.txt", "r");

    if (fptr == NULL)
    {
        printf("\n\t\tYou don't have any previously saved history");
    }
    else
    {
        queue *hist = NULL;

        while (true)
        {
            ch = fgetc(fptr);
            if (ch == EOF)
                break;
            if (ch == '\n')
                counter++;
        }
        fseek(fptr, 0, SEEK_SET);

        while (counter--)
        {
            fgets(tmp_str, sizeof(tmp_str), fptr);
            reci_no = atoi(tmp_str);
            hist = enqueue(hist, reci_no);
        }

        printf("\n");
        design();
        printf("\n");

        printf("\n\t\t\t\t\t:::::::: VIEW HISTORY ::::::::\n");

        while (hist != NULL)
        {
            temp = hist->val;
            hist = dequeue(hist);

            while (temp--)
            {
                fgets(reci_name, sizeof(reci_name), fptr2);
            }

            printf("\n\n\t\t\t\t\t    You viewed %s", reci_name);
            fseek(fptr2, 0, SEEK_SET);
        }
    }

    fclose(fptr);
    fclose(fptr2);

    // getch();
}

// void update_reci()

void print_title()
{
    // system("cls");
    printf("\n\n");
    system("color 06");
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
    system("color 06");
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
    system("color 06");
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
    printf("\n\n\t\t\t\t\t\t   ::::THANK YOU::::\n\n");
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

    // srand(time(0));

    srand(time(0));

    int r, count = 0, track = 0, count2 = 0;

    // char hash[1000], temp[100];

    for (int i = 0; i < 1000; i++)
    {

        r = rand();
        r = r % 50;
        r += 49;

        hash[i] = r;
        // printf("%c ", hash[i]);
    }

    for (int i = 0; i < 100; i++)
    {
        if (arr[i] == '\0' || arr[i] == '\n')
        {
            break;
        }
        track = 5 * i + 5;
        hash[track] = arr[i];
        count2++;
    }

    hash[0] = count2;
    // printf("%s", hash);

    // return hash;
    // getch();
}

bool sign_up()
{
    usr user;
    char ch, ch2, c_pwd[100];
    int i = 0;

    system("cls");
    printf("\n\n");
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t      SIGN UP PAGE\n\n");
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
        else
        {
            user.pwd[i] = ch;
            printf("*");
            i++;
        }
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
        else
        {
            c_pwd[i] = ch2;
            printf("*");
            i++;
        }
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

        remove("history.txt");
        return true;
        // fprintf(fptr, "%s\n", user.pwd);
    }
}

bool sign_in()
{
    system("cls");
    printf("\n\n");
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t    SIGN IN PAGE\n\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    char tmp1[100], tmp2[100];

    printf("\n\n\t\tEnter your username : ");
    scanf("%s", tmp1);
    printf("\n\t\tEnter your password : ");

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
        else
        {
            tmp2[i] = ch;
            printf("*");
            i++;
        }
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

    for (int i = 0; i < temp2[0]; i++)
    {
        // if(tmp2[i] == '\0' || tmp2[i] == '\n')
        // {
        //     break;
        // }

        if (tmp2[i] != temp2[5 * i + 5])
        {
            check = 1;
        }
    }

    printf("\n");
    design();
    printf("\n");

    printf("\n\t\tPress any key to continue...");

    getch();

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
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t      LOGIN PAGE\n\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    int choice, flag;
    bool s1, s2;

    printf("\n\n\t\t\t\t\t    Sign Up               Enter 1");
    printf("\n\t\t\t\t\t    Sign In               Enter 2");
    printf("\n\t\t\t\t\t    Exit                  Enter 3");

    // printf("\n");
    design();
    printf("\n");

    printf("\n\n\t\tEnter your choice = ");
    scanf("%d", &choice);

    // printf("\n");
    design();
    printf("\n");

    printf("\n\t\tPress any key to continue...");

    getch();

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
    system("color 06");
    char a = 177, b = 219;
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");
    printf("\n\n\t\t\t\t\t\t      MAIN MENU\n\n");
    printf("\t\t");
    for (int i = 0; i < 88; i++)
    {
        printf("%c", b);
    }
    printf("\r");
    printf("\t\t");

    int choice, flag;

    printf("\n\n\t\t\t\t        Add New Recipe                Enter 1");
    printf("\n\t\t\t\t        View Recipe(s)                Enter 2");
    printf("\n\t\t\t\t        Update Recipe                 Enter 3");
    printf("\n\t\t\t\t        View History                  Enter 4");
    printf("\n\t\t\t\t        View Profile                  Enter 5");
    printf("\n\t\t\t\t        Exit                          Enter 6");

    printf("\n");
    design();
    printf("\n");

    printf("\n\n\t\tEnter your choice : ");
    scanf("%d", &choice);

    if (choice == 6)
    {
        flag = 6;
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
    else if (choice == 3)
    {
        flag = 3;
    }
    else if (choice == 4)
    {
        return 4;
    }
    else if (choice == 5)
    {
        return 5;
    }

    return flag;
}

void welcome()
{
    printf("\n\n\n\n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\n\n\t\t\t\t\t       FOOD");
    printf("\n\n\t\t\t\t\t      RECIPE");
    printf("\n\n\t\t\t\t\t     GENERATOR");
    printf("\n\n\n\t\t\t\t\t    IIIT KALYANI");
    printf("\n\n\t\t\t\t\t     DSA PROJECT");
    printf("\n\n\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
    printf("\t. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");

    printf("\n\n");
}

int main()
{
    int num, edge, status = VAL, status2 = VAL;

    getch();

    welcome2();

    getch();

    while (status == VAL)
    {
        status = login_pg();
    }

    if (status == 0)
    {
        while (status2 != 6)
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

                init_all(num, visited, ad_mat);

                cns_graph(num, arr, ad_mat);

                calc_in_deg(num, ad_mat, in_deg);

                topo_sort(num, arr, ad_mat, visited, in_deg, head, &(reci_name));
            }
            else if (status2 == 2)
            {
                display_recipe();
            }
            else if (status2 == 3)
            {
                update_reci();
            }
            else if (status2 == 4)
            {
                view_history();
            }
            else if (status2 == 5)
            {
                view_profile();
            }

            printf("\n");
            design();
            printf("\n");

            printf("\n\t\tPress any key to continue...");

            getch();
        }
    }

    thank_you();

    printf("\n\n\n");

    getch();

    return 0;
}
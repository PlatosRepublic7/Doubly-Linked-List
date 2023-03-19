/* 
    Ryan Kitson
    This is my attempt at implementing a doubly-linked list.
    It is tested by running a selection sort algorithm on a list
    of up to one million non-negative integers. Note that it does this by increasing
    the numbers to be sorted by powers of ten, and that the final sort of one million
    may take a while.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include "getnum.h"

struct Node {
    int item;
    struct Node *next;
    struct Node *prev;
};

struct List {
    int size_is_one;
    struct Node *head;
    struct Node *tail;
};

struct List DLL_New();
int DLL_Empty(struct List *list);
int DLL_Length(struct List *list);
int DLL_Contains(struct List *list, int item);
int DLL_Pop(struct List *list);
void DLL_Clear(struct List *list);
void DLL_Push(struct List *list, int item);
void DLL_Append(struct List *list, int item);
int DLL_Remove(struct List *list, int item);
void get_nums_as_DLL(char *inF, struct List *list, int num_to_get);
void DLL_Swap_To_Front(struct List *list, struct Node *node);

struct List selection_sort(struct List *list, int num_elem);

int main() {
    struct List list = DLL_New();
    struct List sorted_list;
    int num_elem;
    /*int count = 1;*/
    long start_time, end_time;
    char *f = "numarr.txt";

    for (num_elem = 10; num_elem <= 1000000; num_elem *= 10) {
        get_nums_as_DLL(f, &list, num_elem);
        start_time = current_timestamp();
        sorted_list = selection_sort(&list, num_elem);  
        end_time = current_timestamp();
        printf("\x1b[1F");
        printf("\x1b[2K");
        printf("Selection Sort with %d Elements: %ld milliseconds\n\n", num_elem, (end_time - start_time));
        DLL_Clear(&sorted_list);
    }

     
    /*
    while (!DLL_Empty(&sorted_list)) {
        if (count % 5 == 0)
            printf("%d\n", DLL_Pop(&sorted_list));
        else
            printf("%d ", DLL_Pop(&sorted_list));
        count++;
    }
    printf("\n");
    */
    
    return 0;
}


struct List selection_sort(struct List *list, int num_elem) {
    struct List sorted_list = DLL_New();
    struct Node *p, *t;
    int min = 100000000, count = 0;
    
    while (!DLL_Empty(list)) {
        for (p = list->head; p != NULL; p = p->next) {
            if (p->item < min) {
                min = p->item;
                t = p;
            }
        }
        DLL_Swap_To_Front(list, t);
        DLL_Append(&sorted_list, DLL_Remove(list, min));
        count++;
        print_progress(count, num_elem);
        min = 100000000;
    }

    return sorted_list;
}

void get_nums_as_DLL(char *inF, struct List *list, int num_to_get) {
    int i = 0, nums_done = 0, num_len = 0, val;
    char c;
    char num_string[9] = ".........";
    FILE *infile = fopen(inF, "r");
    while (1) {
        c = fgetc(infile);
        if (c == EOF)
            break;
        if (isdigit(c)) {
            while (!isspace(c)) {
                num_string[num_len] = c;
                num_len++;
                c = fgetc(infile);
            }
            
            val = convert_to_int(num_string, num_len);
            DLL_Append(list, val);
            nums_done++;
            printf("Building List");
            print_progress(nums_done, num_to_get);
            
            if (nums_done == num_to_get)
                break;
            
            for (i = 0; i < 9; i++) {
                if (num_string[i] == '.')
                    break;
                else
                    num_string[i] = '.';
            }
            num_len = 0;
        }
        else
            continue;
    }
    fclose(infile);
    printf("\x1b[2K");
}

struct List DLL_New() {
    struct List list;
    list.size_is_one = 0;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

int DLL_Length(struct List *list) {
    struct Node *p;
    int n = 0;
    for (p = list->head; p != NULL; p = p->next) {
        ++n;
    }

    return n;
}

int DLL_Empty(struct List *list) {
    return list->head == NULL;
}

int DLL_Contains(struct List *list, int item) {
    struct Node *node;
    for (node = list->head; node != NULL; node = node->next) {
        if (node->item == item)
            return 1;
    }

    return 0;
}

int DLL_Pop(struct List *list) {
    struct Node *node = list->head;
    int item = node->item;
    list->head = node->next;
    if (DLL_Empty(list)) {
        list->tail = NULL;
    }
    else
        list->head->prev = NULL;
    free(node);
    return item;
}

void DLL_Clear(struct List *list) {
    while (!DLL_Empty(list))
        DLL_Pop(list);
}

void DLL_Push(struct List *list, int item) {
    struct Node *node = malloc(sizeof(struct Node));
    node->item = item;
    node->prev = NULL;
    if (DLL_Empty(list)) {
        node->next = list->head;
        list->tail = node;
        list->head = node;
        list->size_is_one = 1;
    }
    else {
        if (list->size_is_one) {
            list->tail->prev = node;
            node->next = list->tail;
            list->head = node;
            list->size_is_one = 0;
        }
        else {
            node->next = list->head;
            list->head->prev = node;
            list->head = node;
        }
    }
}

void DLL_Append(struct List *list, int item) {
    if (DLL_Empty(list)) {
        DLL_Push(list, item);
    }
    else {
        struct Node *node = malloc(sizeof(struct Node));
        node->item = item;
        node->next = NULL;
        if (list->size_is_one) {
            node->prev = list->head;
            list->tail->next = node;
            list->tail = node;
            list->size_is_one = 0;
        }
        else {
            node->prev = list->tail;
            list->tail->next = node;
            list->tail = node;
        }
    }
}

int DLL_Remove(struct List *list, int item) {
    struct Node *node, *temp;
    int n_item = -1;
    for (node = list->head; node != NULL; node = node->next) {
        if (node->item == item) {
            n_item = node->item;
            if (node->next == NULL && node->prev == NULL) {
                free(node);
                list->head = NULL;
                list->tail = NULL;
            }
            else if (node->prev == NULL) {
                temp = node->next;
                temp->prev = NULL;
                list->head = temp;
                free(node);
            }
            else if (node->next == NULL) {
                temp = node->prev;
                temp->next = NULL;
                list->tail = temp;
                free(node);
            }
            else {
                temp = node->prev;
                temp->next = node->next;
                node->next->prev = temp;
                free(node);
            }
            break;
        }
    }

    return n_item;
}

void DLL_Swap_To_Front(struct List *list, struct Node *node) {
    int temp = -1;

    temp = node->item;
    node->item = list->head->item;
    list->head->item = temp;
}

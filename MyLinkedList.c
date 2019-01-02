//
// Created by Mahan on 1/2/2019.
//

#include "MyFile.h"
#include "MyLinkedList.h"


#define DEBUG

struct Node *Add_Node(struct Problem_Unit info) {
    struct Node *tmp = malloc(sizeof(struct Node));

    tmp->data = info;
    tmp->next = NULL;
    return tmp;
}

void Remove_Node(struct Node **list, struct Node *target) {
    if (*list == target) {
        *list = target->next;
        free(target);
        return;
    }
    struct Node *current = *list;
    while (current->next != target)
        current = current->next;
    current->next = target->next;
    free(target);
}

int Node_Counter(struct Node *list) {
    int n = 0;
    for (struct Node *current = list; current != NULL; current = current->next, n++);
    return n;
}

struct Node *Random_Node_Finder(int *chance_sum, struct Node *list) {
    srand(time(NULL));
    int random_counter = rand() % (*chance_sum);

    struct Node *current = list;
    while (1) {
        random_counter -= (current->data).chance;
        if (random_counter <= 0) {
            ((current->data).chance)--;
            (*chance_sum)--;
            return current;
        }
        current = current->next;
    }
}

void Check_List(struct Node **list) {
    struct Node *current = *list;
    while (current != NULL) {
        if (((current->data).chance) == 0) {
            struct Node *tmp = current;
            current = current->next;
            Remove_Node(list, tmp);
        } else
            current = current->next;
    }
}

void Print_List(struct Node *list) {
    for (struct Node *current = list; current != NULL; current = current->next) {
        struct Problem_Unit tmp = current->data;
        printf("%s", tmp.problem);
        printf("%s", tmp.choice1);
        printf("Peaple: %d Court: %d Trasury: %d\n", tmp.people1, tmp.court1, tmp.treasury1);
        printf("%s", tmp.choice2);
        printf("Peaple: %d Court: %d Trasury: %d\n", tmp.people2, tmp.court2, tmp.treasury2);
        printf("Chance: %d\n", tmp.chance);
    }

}


struct Node *Create_List(int *chance_sum) {
    struct Node *list = NULL, *current = NULL;
    int n = 1;

    FILE *Mother_File = Open_In_File("CHOICES.txt");
    if (Mother_File == NULL) {
        printf("Error Problem file not found\n");
        exit(-1);
    }

    while (1) {
        char file_name[20];
        if (feof(Mother_File))
            break;
        fscanf(Mother_File, "%s", file_name);

        FILE *fp = Open_In_File(file_name);
        if (fp == NULL)
            break;
        struct Problem_Unit tmp;
        tmp = Scan_In_Problem(fp, chance_sum);
        if (list == NULL) {
            list = Add_Node(tmp);
            current = list;
        } else {
            current->next = Add_Node(tmp);
            current = current->next;
        }
        fclose(fp);
        n++;
    }
    fclose(Mother_File);

    return list;
}

struct Node *Load_list(FILE **fload) {
    struct Node *list = NULL, *current = NULL;
    int n;
    fread(&n, sizeof(int), 1, *fload);
    struct Problem_Unit tmp;
    for (int i = 0; i < n; i++) {
        fread(&tmp, sizeof(struct Problem_Unit), 1, *fload);
        if(i == 0){
            list = Add_Node(tmp);
            current = list;
        } else{
            current->next = Add_Node(tmp);
            current = current->next;
        }
    }
    return list;
}

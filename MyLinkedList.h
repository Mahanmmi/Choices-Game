//
// Created by Mahan on 1/2/2019.
//

#ifndef INTRO_PROGRAMMING_FINAL_PROJECT_MYLINKEDLIST_H
#define INTRO_PROGRAMMING_FINAL_PROJECT_MYLINKEDLIST_H

#include "MyFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Problem_Unit {
    char problem[200];
    char choice1[200];
    int people1, court1, treasury1;
    char choice2[200];
    int people2, court2, treasury2;
    int chance;
};

struct Node {
    //Data
    struct Problem_Unit data;
    //Pointer to next
    struct Node *next;
};

struct Node *Add_Node(struct Problem_Unit info);

void Remove_Node(struct Node **list, struct Node *target);

int Node_Counter(struct Node * list);

struct Node *Random_Node_Finder(int *chance_sum, struct Node *list);

void Check_List(struct Node **list);

void Print_List(struct Node *list);

struct Node *Create_List(int * chance_sum);

struct Node *Load_list(FILE **fload);

#endif //INTRO_PROGRAMMING_FINAL_PROJECT_MYLINKEDLIST_H

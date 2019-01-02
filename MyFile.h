//
// Created by Mahan on 1/2/2019.
//


#ifndef INTRO_PROGRAMMING_FINAL_PROJECT_MYFILE_H
#define INTRO_PROGRAMMING_FINAL_PROJECT_MYFILE_H
//
#include <stdio.h>
#include "MyLinkedList.h"



FILE *Open_In_File(char * file_name);

struct Problem_Unit Scan_In_Problem(FILE *fp, int * chance_sum);

void Save_Game(struct Node *list, int chance_sum, int people, int court, int treasury);

struct Node *Load_Game(int *chance_sum, int *people, int *court, int *treasury);

#endif //INTRO_PROGRAMMING_FINAL_PROJECT_MYFILE_H

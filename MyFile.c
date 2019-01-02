//
// Created by Mahan on 1/2/2019.
//


#include "MyFile.h"
#include "MyLinkedList.h"
#include <string.h>

#define DEBUG

FILE *Open_In_File(char * name) {
    FILE *fp;
    char *prefix = "..\\";
    char file_name[30];
    strcpy(file_name, "");
    strcat(file_name, prefix);
    strcat(file_name, name);
#ifdef DEBUG
    puts(file_name);
#endif
    fp = fopen(file_name, "r");
    return fp;
}

struct Problem_Unit Scan_In_Problem(FILE *fp) {
    struct Problem_Unit tmp;
    fgets(tmp.problem, 200, fp);
    fgets(tmp.choice1, 200, fp);
    fscanf(fp, "%d%d%d", &tmp.people1, &tmp.court1, &tmp.treasury1);
    fgetc(fp);
    fgets(tmp.choice2, 200, fp);
    fscanf(fp, "%d%d%d", &tmp.people2, &tmp.court2, &tmp.treasury2);
    tmp.chance = 3;
    fclose(fp);
    return tmp;
}
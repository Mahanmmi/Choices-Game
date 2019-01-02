//
// Created by Mahan on 1/2/2019.
//


#include "MyFile.h"
#include "MyLinkedList.h"
#include <string.h>

#define DEBUG

struct Node *Start_New_Game(int *chance_sum, int *people, int *court, int *treasury) {
    *people = 50;
    *court = 50;
    *treasury = 50;
    struct Node *list = Create_List(chance_sum);
    return list;
}

FILE *Open_In_File(char *name) {
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

struct Problem_Unit Scan_In_Problem(FILE *fp, int *chance_sum) {
    struct Problem_Unit tmp;
    fgets(tmp.problem, 200, fp);
    fgets(tmp.choice1, 200, fp);
    fscanf(fp, "%d%d%d", &tmp.people1, &tmp.court1, &tmp.treasury1);
    fgetc(fp);
    fgets(tmp.choice2, 200, fp);
    fscanf(fp, "%d%d%d", &tmp.people2, &tmp.court2, &tmp.treasury2);
    tmp.chance = 3;
    (*chance_sum) += tmp.chance;
    fclose(fp);
    return tmp;
}

struct Node *Load_Game(int *chance_sum, int *people, int *court, int *treasury,char * name) {
    FILE * fload = fopen("..\\save.bin", "rb");

    int is_end;
    fread(&is_end, sizeof(int), 1, fload);
    int k;
    fread(&k, sizeof(int), 1, fload);
    fread(name, sizeof(char), k+1, fload);
    struct Node *list;
    if(is_end == 0) {
        list = Load_list(&fload);
        fread(chance_sum, sizeof(int), 1, fload);
        fread(people, sizeof(int), 1, fload);
        fread(court, sizeof(int), 1, fload);
        fread(treasury, sizeof(int), 1, fload);
        fclose(fload);
    } else {
        list = Start_New_Game(chance_sum,people,court,treasury);
    }

    return list;
}
//
void Save_Game(struct Node *list, int chance_sum, int people, int court, int treasury, char * name, int is_end) {
    FILE *fout = fopen("..\\save.bin", "wb");

    fwrite(&is_end, sizeof(int), 1, fout);

    int k = strlen(name);
    fwrite(&k, sizeof(int), 1, fout);
    fwrite(name, sizeof(char), k+1, fout);

    int n = Node_Counter(list);
    fwrite(&n, sizeof(int), 1, fout);

    for (struct Node *current = list; current != NULL; current = current->next) {
        fwrite(&(current->data), sizeof(struct Problem_Unit), 1, fout);
    }

    fwrite(&chance_sum, sizeof(int), 1, fout);
    fwrite(&people, sizeof(int), 1, fout);
    fwrite(&court, sizeof(int), 1, fout);
    fwrite(&treasury, sizeof(int), 1, fout);


    fclose(fout);
}
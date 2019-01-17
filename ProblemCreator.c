//
// Created by Mahan on 1/17/2019.
//

#include "MyLinkedList.h"
#include "MyFile.h"
#include "ProblemCreator.h"
#include <string.h>


struct Problem_Unit get_problem(char *p_name) {
    struct Problem_Unit tmp;
    fflush(stdin);
    printf("Problem file name? (without .txt)\n");
    gets(p_name);
    strcat(p_name,".txt");
    fflush(stdin);
    printf("Problem?\n");
    gets(tmp.problem);
    strcat(tmp.problem, "\n");
    printf("Choice 1?\n");
    gets(tmp.choice1);
    strcat(tmp.choice1, "\n");
    printf("People/Court/Treasury change of choice 1?\n");
    scanf("%d%d%d", &tmp.people1, &tmp.court1, &tmp.treasury1);
    fflush(stdin);
    printf("Choice 2?\n");
    gets(tmp.choice2);
    strcat(tmp.choice2, "\n");
    printf("People/Court/Treasury change of choice 2?\n");
    scanf("%d%d%d", &tmp.people2, &tmp.court2, &tmp.treasury2);
    return tmp;
}

void add_problem(struct Problem_Unit in,char *p_name) {
    char file_name[200] = "..\\";
    strcat(file_name,p_name);
    FILE *fp = fopen(file_name, "w");
    fprintf(fp,"%s%s%d\n%d\n%d\n%s%d\n%d\n%d",in.problem,in.choice1,in.people1,in.court1,in.treasury1,in.choice2,in.people2,in.court2,in.treasury2);
    fclose(fp);
    fp=fopen("..\\CHOICES.txt","a");
    fprintf(fp,"\n%s",p_name);
    fclose(fp);
}
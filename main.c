#include "MyLinkedList.h"
#include "MyFile.h"

int People, Court, Treasury;

int initialize_game() {
    printf("\tWhat do you want to do?\n");
    printf("\t1: Start a new game\n");
    printf("\t2: Resume last saved game\n");
    printf("\t3: Tutorial\n");
    int operation;
    scanf("%d", &operation);
    if (operation == 2 || operation == 1)
        return operation;
    if (operation == 3) {
        FILE *tutor = Open_In_File("Game_Tutorial.txt");
        while (1) {
            if (feof(tutor))
                break;
            char tmp_str[200];
            fgets(tmp_str, 200, tutor);
            printf("%s", tmp_str);
        }
        fclose(tutor);
    } else {
        printf("Error invalid input!\n");
    }
    while (1) {
        printf("\tWhat do you want to do?\n");
        printf("\t1: Start a new game\n");
        printf("\t2: Resume last saved game\n");
        scanf("%d", &operation);
        if (operation == 2 || operation == 1)
            return operation;
        printf("Error invalid input!\n");
    }
}

struct Node *Start_New_Game(int *chance_sum) {
    People = 50;
    Court = 50;
    Treasury = 50;
    struct Node *list = Create_List(chance_sum);
    return list;
}


int main() {

    printf("\t\tWelcome to great game of decisions\n");
    int mode = initialize_game();
    int chance_sum;
    struct Node *list;
    while (1) {
        if (mode == 1) {
            list = Start_New_Game(&chance_sum);
            break;
        } else if (mode == 2) {
            FILE *fp = fopen("..\\save.bin", "rb");
            if (fp == NULL) {
                printf("You have no saved game");
                mode = initialize_game();
                fclose(fp);
            } else {
                list = Load_Game(&chance_sum, &People, &Court, &Treasury);
                fclose(fp);
                break;
            }
        }
    }









    /*
    int chance_sum = 0;
    struct Node *list = Create_List(&chance_sum);
    Print_List(list);
    printf("%d\n", chance_sum);


    while (chance_sum > 5) {
        struct Node *rnd_node = Random_Node_Finder(&chance_sum, list);
        struct Problem_Unit tmp = rnd_node->data;
        Check_List(&list);
        printf("Random : %s %d\n", (tmp.problem), (tmp.chance));
    }


    for (struct Node *current = list; current != NULL; current = current->next) {
        struct Problem_Unit tmp = current->data;
        printf("%s %d\n", (tmp.problem), (tmp.chance));
    }
*/
    return 0;
}
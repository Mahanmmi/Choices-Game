#include "MyLinkedList.h"
#include "MyFile.h"
#include <stdbool.h>

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

bool check_end(){
    if (People <= 0 || Court <= 0 || Treasury <= 0)
        return 1;
    if (((People + Court + Treasury) / 3) < 10)
        return 1;
    return 0;
}

void print_resources(){
    printf("People: %d Court: %d Treasury: %d\n",People,Court,Treasury);
}

void Game(struct Node *list, int *chance_sum, char *name) {
    print_resources();
    while (1) {

        if (list == NULL) {
            list = Create_List(chance_sum);
        }

        struct Node *rnd = Random_Node_Finder(chance_sum, list);
        struct Problem_Unit data = rnd->data;
        printf("%s", data.problem);
        printf("<<<< %s", data.choice1);
        printf(">>>> %s ", data.choice2);
        char op;
        scanf(" %c", &op);
        while (1) {
            if (op == '<') {
                People += data.people1;
                Court += data.court1;
                Treasury += data.treasury1;
                break;
            } else if (op == '>') {
                People += data.people2;
                Court += data.court2;
                Treasury += data.treasury2;
                break;
            } else if (op == 'p') {
                printf("Game paused\n Save and exit? (Y/N)");
                while (1) {
                    char save;
                    scanf(" %c", &save);
                    if (save == 'Y') {
                        Save_Game(list, *chance_sum, People, Court, Treasury, name, 0);
                        exit(0);
                    } else if (save == 'N') {
                        break;
                    } else {
                        printf("Error invalid input (Enter Y / N)\n");
                    }

                }
            } else {
                printf("Error invalid input (Enter < / > / p)\n");
            }
        }
        print_resources();
        if (check_end()) {
            printf("Game is over too bad :(\n Do you want to save? (Y/N)");
            while (1) {
                char save;
                scanf("%c", &save);
                if (save == 'Y') {
                    Save_Game(list, *chance_sum, People, Court, Treasury, name, 1);
                    exit(0);
                } else if (save == 'N') {
                    exit(0);
                } else {
                    printf("Error invalid input (Enter Y / N)\n");
                }
            }
        }

    }
}

int main() {

    printf("\t\tWelcome to great game of decisions\n");
    printf("Enter your name : ");
    char name[50];
    scanf("%s", name);
    int mode = initialize_game();
    int chance_sum = 0;

    struct Node *list;
    while (1) {
        if (mode == 1) {
            list = Start_New_Game(&chance_sum,&People,&Court,&Treasury);
            break;
        } else if (mode == 2) {
            FILE *fp = fopen("..\\save.bin", "rb");
            if (fp == NULL) {
                printf("You have no saved game");
                mode = initialize_game();
                fclose(fp);
            } else {
                list = Load_Game(&chance_sum, &People, &Court, &Treasury, name);
                fclose(fp);
                break;
            }
        }
    }
    Game(list, &chance_sum, name);
    return 0;
}
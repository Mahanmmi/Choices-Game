#include "MyLinkedList.h"
#include "MyFile.h"
#include <stdbool.h>

int People, Court, Treasury;

int initialize_game() {
    printf("\tWhat do you want to do?\n");
    printf("\t1: Start a new game\n");
    printf("\t2: Resume last saved game\n");
    printf("\t3: Tutorial\n");
    printf("\t4: Show leaderboard\n");
    char operation;
    fflush(stdin);
    scanf(" %c", &operation);
    if (operation == '2' || operation == '1')
        return operation - '0';
    if (operation == '3') {
        FILE *tutor = Open_In_File("Game_Tutorial.txt");
        while (1) {
            if (feof(tutor))
                break;
            char tmp_str[200];
            fgets(tmp_str, 200, tutor);
            printf("%s", tmp_str);
        }
        fclose(tutor);
    } else if (operation == '4'){
        show_leaderboard();
    } else {
        printf("Error invalid input!\n");
    }
    while (1) {
        printf("\tWhat do you want to do?\n");
        printf("\t1: Start a new game\n");
        printf("\t2: Resume last saved game\n");
        fflush(stdin);
        scanf(" %c", &operation);
        if (operation == '2' || operation == '1')
            return operation - '0';
        printf("Error invalid input!\n");
    }
}

bool check_end() {
    if (People <= 0 || Court <= 0 || Treasury <= 0)
        return 1;
    if (((People + Court + Treasury) / 3) < 10)
        return 1;
    return 0;
}

void print_resources() {
    printf("People: %d Court: %d Treasury: %d\n", People, Court, Treasury);
}

void Game(struct Node *list, int *chance_sum, char *name) {
    print_resources();
    while (1) {

        if (list == NULL) {
            list = Create_List(chance_sum);
        }

        struct Node *rnd = Random_Node_Finder(chance_sum, list);
        Check_List(&list);
        struct Problem_Unit data = rnd->data;
        printf("%s", data.problem);
        printf("<<<< %s", data.choice1);
        printf(">>>> %s ", data.choice2);
        while (1) {
            char op;
            fflush(stdin);
            scanf(" %c", &op);
            if (op == '<') {
                People += data.people1;
                Court += data.court1;
                Treasury += data.treasury1;
                if(People>100)
                    People=100;
                if(Court>100)
                    Court=100;
                if(Treasury>100)
                    Treasury=100;
                break;
            } else if (op == '>') {
                People += data.people2;
                Court += data.court2;
                Treasury += data.treasury2;
                if(People>100)
                    People=100;
                if(Court>100)
                    Court=100;
                if(Treasury>100)
                    Treasury=100;
                break;
            } else if (op == 'p') {
                printf("Game paused\n Save and exit? (Y/N)\n");
                while (1) {
                    char save;
                    fflush(stdin);
                    scanf(" %c", &save);
                    if (save == 'Y') {
                        Save_Game(list, *chance_sum, People, Court, Treasury, name, 0);
                        exit(0);
                    } else if (save == 'N') {
                        exit(0);
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
            update_leaderboard(name, People, Court, Treasury);
            printf("Game is over too bad :(\n Do you want to save? (Y/N)\n");
            while (1) {
                char save;
                fflush(stdin);
                scanf(" %c", &save);
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
    char name[50];
    int mode = initialize_game();
    int chance_sum = 0;

    struct Node *list;
    while (1) {
        if (mode == 1) {
            printf("Enter your name : ");
            scanf("%s", name);
            list = Start_New_Game(&chance_sum, &People, &Court, &Treasury);
            break;
        } else if (mode == 2) {
            FILE *fp = fopen("..\\save.bin", "rb");
            if (fp == NULL) {
                printf("You have no saved game");
                mode = initialize_game();
                fclose(fp);
            } else {
                list = Load_Game(&chance_sum, &People, &Court, &Treasury, name);
                printf("Hello %s\n",name);
                fclose(fp);
                break;
            }
        }
    }
    Game(list, &chance_sum, name);
    return 0;
}
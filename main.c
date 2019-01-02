#include "MyLinkedList.h"
#include "MyFile.h"



int main() {
    /*int n,C_sum = 0; //
    scanf("%d", &n);
    struct Node * List = NULL , * current = NULL;
    for(int i=0;i<n;i++){
        struct Problem_Unit tmp = {0};
        scanf("%s%d",(tmp.problem),&(tmp.chance));
        C_sum += tmp.chance;
        if(i == 0){
            List = Add_Node(tmp);
            current = List;
        } else {
            current -> next = Add_Node(tmp);
            current = current -> next;
        }
    }
    while(C_sum>5){
        struct Node * rnd_node = Random_Node_Finder(&C_sum,List);
        struct Problem_Unit tmp = rnd_node -> data;
        Check_List(&List);
        printf("Random : %s %d\n",(tmp.problem),(tmp.chance));
    }


    for(current = List;current != NULL;current = current -> next){
        struct Problem_Unit tmp = current -> data;
        printf("%s %d\n",(tmp.problem),(tmp.chance));
    }*/

    struct Node * list = Create_List();
    Print_List(list);

    return 0;
}
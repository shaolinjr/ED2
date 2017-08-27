#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ARTHUR DE CASTRO L. PIRES
// Prototypes

struct listItem {
    int number;
    struct listItem *prox;
    struct listItem *ant;
};

typedef struct listItem listItem;

listItem* createList ();
listItem *add (listItem *list, int number);
void printList (listItem *list);
listItem *removeItem (listItem *list, int number);
int generateCode ();
void menu (listItem *list);


int main() {
    setbuf(stdout, NULL);
    listItem *list = createList();
//    list = add(list, generateCode());
//    list = add(list, 10);
//    list = add(list, 12);
//    printList(list);
//    list = removeItem(list,generateCode());
//    printf("**************\n");
//    printList(list);
//    printf("**************\n");
//    list = removeItem(list,12);
//    printList(list);
//    printf("**************\n");
//    list = removeItem(list,generateCode());
//    printList(list);
//    list = removeItem(list,10);
//    printf("**************\n");
//
//    printList(list);
    menu(list);
    return 0;
}

listItem* createList (){
    listItem *list = (listItem*) malloc(sizeof(listItem));

    list->number    = NULL;
    list->ant       = NULL;
    list->prox      = NULL;

    return list;
}


// inserstion will be always on the head of the list
listItem *add (listItem *list, int number){

    listItem *temp = list;
    // list was never inserted
    if (temp->number == NULL){
        temp->prox = NULL;
        temp->number = number;
        temp->ant = NULL;
        return temp;
    }else{
        listItem *newItem = (listItem*) malloc(sizeof(listItem));
        newItem->ant = NULL;
        newItem->number = number;
        newItem->prox = temp;
        temp->ant = newItem;
        return newItem;
    }
}


listItem *removeItem (listItem *list, int number){
    listItem *current = list;
    listItem *newHead = NULL;
    char excluiu = 'N';

    // we will use the idea of middle-out
    // get the inside elements, then get the head and tail
    while(current->prox != NULL){
        // is not the head
        if(current->ant != NULL){
            // we are sure that is in the middle part
            if(current->number == number){
                // we have to make the previous point to the next of the current
                // and the next of the current point the previous of the current
                current->ant->prox = current->prox;
                current->prox->ant = current->ant;
                free(current);
                excluiu = 'S';
                break;
            }
        }else{
            // we are the head so we have to make the next of the current be the newHead
            if (current->number == number){
                newHead = current->prox;
                newHead->ant = NULL;
                free(current);
                return newHead;
            }
        }
        // we haven't find it yet
        current = current->prox;
    }

    // last chance to find our guy
    if(excluiu == 'N' && current->prox == NULL) {
        if (current->ant != NULL) {
            if (current->number == number) {
                current->ant->prox = NULL;
                free(current);
            }
        }else{
            if (current->number == number){
                newHead = createList();
                return newHead;
            }
        }
    }else if (excluiu == 'N'){
        printf("Item not found in this list!");
    }

    return list;


}

void printList (listItem *list){
    listItem *temp = list;
    printf("******* LISTA *********\n");
    while(temp->prox != NULL){
        printf("Number: %d\n", temp->number);
        temp = temp->prox;
    }
    if(temp->prox == NULL && temp->number != NULL){
        printf("Number: %d\n", temp->number);
    }else if (temp->number == NULL){
        printf("Empty list!\n");
    }
    printf("************************\n");

}

int generateCode (){
    srand(time(NULL));
    return rand() % 100;
}

void menu (listItem *list){
    int opcao = -1;
    int number;

    while (opcao !=  4){
        printf("1) Inserir item\n");
        printf("2) Remove item\n");
        printf("3) Exibir itens\n");
        printf("4) Sair\n");
        printf("Qual a opção: ");
        fflush(stdin);
        scanf("%d", &opcao);
        while (opcao < 1 || opcao > 4){
            printf("Opção inválida. Tente novamente: ");
            scanf("%d", &opcao);
        }

        switch(opcao){
            case 1:
                printf("Digite o código: ");
                scanf("%d",&number);
                list = add(list, number);
                break;
            case 2:
                printf("Digite o código: ");
                scanf("%d",&number);
                list = removeItem(list, number);
                break;
            case 3:
                printList(list);
                break;

        }
        if (opcao == 4){
            printf("Saindo...");
            break;
        }

    }
}
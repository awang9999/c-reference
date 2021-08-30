#include <stdio.h>
#include "linkedlist.h"

int main(){
    printf("To C or not to C: that is the question.\n");

    LinkedList* mylinkedlist = LinkedList__create(sizeof(int));

    mylinkedlist->sanity_check();

    return 0;
}
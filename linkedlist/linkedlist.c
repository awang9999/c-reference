#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

bool LinkedList__destroy(LinkedList* self){
    
    Node * curr = self->head;

    while(curr != NULL){
        Node * tmp = curr->next;
        free(curr);
        curr = tmp;
    }

    free(self);

    return true;
}

// The head of the linkedlist is the position at which push and pop occur
bool LinkedList__push(LinkedList* self, void *elem){    
    Node * newnode = (Node *)malloc(sizeof(Node));
    newnode->data = elem;
    newnode->next = self->head;
    self->head = newnode;
    (self->size)++;
    return true;
}
void* LinkedList__pop(LinkedList* self){
    Node* first_node = self->head;
    void* elem = first_node->data;
    self->head = first_node->next;
    free(first_node);
    (self->size)--;
    return elem;
}

bool LinkedList__insert(LinkedList* self, void* elem, int index)
{
    // TODO
    return false;
}

bool LinkedList__contains(LinkedList* self, void* target){
    // TODO
    return false;
}

void* LinkedList__get(LinkedList* self, int index){
    if(index > self->size){
        return NULL;
    }
    Node * curr = self->head;
    //TEST FOR EDGE CASE
    for(int i = 0; i <= index; i++){
        curr = curr->next;
    }

    return curr->data;
}

bool LinkedList__replaceAt(LinkedList* self, void* elem, int index){
    // TODO
    return false;
}

bool LinkedList__replace(LinkedList* self, void* old_val, void* new_val){
    // TODO
    return false;
}

bool LinkedList__remove(LinkedList* self, void* target){
    // TODO
    return false;
}

void* LinkedList__removeAt(LinkedList* self, int index){
    // TODO
    return NULL;
}

bool LinkedList__isEmpty(LinkedList* self){
    return (self->size == 0);
}

void LinkedList__sanitycheck(){
    printf("linkedlist.c is successfully included!\n");
}

LinkedList* linkedlist__create (unsigned int dataSize){
    LinkedList* llist = (LinkedList*)malloc(sizeof(LinkedList));

    llist->super = NULL; // A generic linked list has no super class
    llist->head = NULL; // The head of the list is initially nothing
    llist->size = 0; // A linked list is initially empty
    llist->data_size = dataSize;

    llist->destroy = LinkedList__destroy;
    llist->push = LinkedList__push;
    llist->pop = LinkedList__pop;
    llist->insert = LinkedList__insert;
    llist->contains = LinkedList__contains;
    llist->get = LinkedList__get;
    llist->replace_at = LinkedList__replaceAt;
    llist->replace = LinkedList__replace;
    llist->remove_at = LinkedList__removeAt;
    llist->remove = LinkedList__remove;
    llist->is_empty = LinkedList__isEmpty;
    llist->sanity_check = LinkedList__sanitycheck;

    return llist;
}

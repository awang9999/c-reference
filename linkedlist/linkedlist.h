#include <stdio.h>
#include <stdbool.h>

typedef struct LinkedList_t LinkedList;

typedef bool (*fptrDestroy)(LinkedList *);

typedef bool (*fptrPush)(LinkedList *, void*);
typedef void* (*fptrPop)(LinkedList *);

typedef bool (*fptrInsert)(LinkedList *, void*, int);
typedef bool (*fptrContains)(LinkedList *, void*);
typedef void* (*fptrGet)(LinkedList *, int);
typedef bool (*fptrReplaceAt)(LinkedList *, void*, int);
typedef bool (*fptrReplace)(LinkedList *, void*, void*);
typedef bool (*fptrRemove)(LinkedList *, void*);
typedef void* (*fptrRemoveAt)(LinkedList *, int);
typedef bool (*fptrIsEmpty)(LinkedList *);

typedef void (*fptrSanityCheck)();

typedef struct Node_t{
    void* data;
    struct Node* next;
} Node;

typedef struct LinkedList_t
{
    void *super;
    struct Node *head;
    int size;
    int data_size;

    fptrDestroy destroy;
    fptrPush push;
    fptrPop pop;
    fptrInsert insert;
    fptrContains contains;
    fptrGet get;
    fptrReplaceAt replace_at;
    fptrReplace replace;
    fptrRemoveAt remove_at;
    fptrRemove remove;
    fptrIsEmpty is_empty;
    fptrSanityCheck sanity_check;

} LinkedList;

void linkedlist__sanitycheck();

LinkedList* LinkedList__create (unsigned int dataSize);
bool Linkedlist__destroy(LinkedList* self);
// The head of the linkedlist is the position at which push and pop occur
bool Linkedlist__push(LinkedList* self, void *elem);
void* Linkedlist__pop(LinkedList* self);

bool Linkedlist__insert(LinkedList* self, void* elem, int index);
bool Linkedlist__contains(LinkedList* self, void* target);
void* Linkedlist__get(LinkedList* self, int index);
bool Linkedlist__replaceAt(LinkedList* self, void* elem, int index);
bool Linkedlist__replace(LinkedList* self, void* old_val, void* new_val);
bool Linkedlist__remove(LinkedList* self, void* target);
void* Linkedlist__removeAt(LinkedList* self, int index);
bool Linkedlist__isEmpty(LinkedList* self);

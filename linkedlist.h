
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct
{
    LinkedListNode *head;
    LinkedListNode *tail;
    int count;
} LinkedList;

LinkedList *createLinkedList();
LinkedListNode *tailNode(LinkedList *list);
void insertStart(LinkedList *list, void *entry);
void *removeStart(LinkedList *list);
void insertLast(LinkedList *list, void *entry);
void *removeLast(LinkedList *list);

typedef void (*listFunc)(void *data);
typedef void (*listToFileFunc)(FILE* file, void *data);
void printLinkedList(LinkedList *list, listFunc funcPtr);
void printLinkedListToFile(LinkedList *list,char* filename, listToFileFunc funcPtr);
void freeLinkedList(LinkedList* list, listFunc funcPtr);

void *getNodeData(LinkedList *list, int nodeIndex);

#endif
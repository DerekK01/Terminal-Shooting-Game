#include <stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

/* create the linkedlist */
LinkedList *createLinkedList()
{
    LinkedList *list;
    list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

/* get the last node */
LinkedListNode *tailNode(LinkedList *list)
{
    LinkedListNode *currentNode;
    currentNode = list->head;
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    return currentNode;
}

/* insert data from the start */
void insertStart(LinkedList *list, void *entry)
{
    LinkedListNode *newNode;
    newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->prev = NULL;
    newNode->next = list->head;
    if (list->head != NULL)
    {
        list->head->prev = newNode;
    }
    list->head = newNode;
    list->count++;
    list->tail = tailNode(list);
}

/* remove the first node */
void *removeStart(LinkedList *list)
{
    LinkedListNode *temp;
    void* listData;
    temp = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->tail = tailNode(list);
    list->count--;
    listData = temp->data;
    free(temp);
    return listData;
}

/* insert data from the end */
void insertLast(LinkedList *list, void *entry)
{
    LinkedListNode *newNode;
    newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->prev = list->tail;
    newNode->next = NULL;
    if (list->tail == NULL)
    {
        list->head = newNode;
    }
    else
    {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->count++;
}

/* remove the last node */
void *removeLast(LinkedList *list)
{
    LinkedListNode *temp;
    void *listData;
    temp = list->tail;
    list->tail->prev->next = NULL;
    list->tail = list->tail->prev;
    list->count--;
    listData = temp->data;
    free(temp);
    return listData;
}

/* print the whole linked list */
void printLinkedList(LinkedList *list, listFunc funcPtr)
{
    LinkedListNode *currentNode;
    currentNode = list->head;
    while (currentNode != NULL)
    {
        funcPtr(currentNode->data);
        currentNode = currentNode->next;
    }
}

/* print the whole linkedlist to an output file */
void printLinkedListToFile(LinkedList *list,char* filename, listToFileFunc funcPtr)
{
    FILE *file = fopen(filename, "w+");
    LinkedListNode *currentNode;
    currentNode = list->head;
    while (currentNode != NULL)
    {
        funcPtr(file,currentNode->data);
        currentNode = currentNode->next;
    }
    fclose(file);
}


/* free the whole linked list */
void freeLinkedList(LinkedList* list, listFunc funcPtr)
{
    LinkedListNode *currentNode, *nextNode;
    currentNode = list->head;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        funcPtr(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}

/* get the data from a specific node*/
void *getNodeData(LinkedList *list, int nodeIndex)
{
    LinkedListNode* currentNode;
    int i;
    currentNode = list->head;
    for(i=0; i< nodeIndex;i++)
    {
        currentNode = currentNode->next;
    }
    return currentNode->data;

} 
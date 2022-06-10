//
// Created by Seb on 30-May-2022.
//

#ifndef DATASTRUCTURES_DOUBLYLINKEDLIST_H
#define DATASTRUCTURES_DOUBLYLINKEDLIST_H

/*
 * Base component the doubly linked list. Should not be used directly in
 * user's program.
 */
typedef struct Node {
    int item;
    struct Node* next;
    struct Node* prev;
} Node;

Node *nodeInit(int data);

/* A linked list that can be traversed forward and backwards.
 *
 * len stores the length of the list and is automatically updated with
 * every function call that mutates the linked list.
 */
typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
    int len;
} DoublyLinkedList;

DoublyLinkedList* lListInit();

/*
 * Operations:
 *      insert - adds data at the index'th position in lList. Indexes start
 *               at 0.
 *      remove - deletes an item in lList at index
 *
 *      find   - returns the index of data in lList. Returns -1 if not found.
 */
void insert(DoublyLinkedList* lList, int data, int index);
void removeIdx(DoublyLinkedList* lList, int index);
int find(DoublyLinkedList* lList, int data);
void printList(DoublyLinkedList* lList);
void destroy(DoublyLinkedList* lList);

#endif //DATASTRUCTURES_DOUBLYLINKEDLIST_H

//
// Created by Seb on 30-May-2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "DoublyLinkedList.h"

Node* nodeInit(int data){
    Node* node = malloc(sizeof (Node));
    node->item = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

struct DoublyLinkedList* lListInit(){
    struct DoublyLinkedList* lList = malloc(sizeof (DoublyLinkedList));
    lList->head = NULL;
    lList->tail = NULL;
    lList->len = 0;
    return lList;
}

void insert(struct DoublyLinkedList* lList, int data, int index){
    Node* newNode = nodeInit(data);
    lList->len++;
    // empty linked list
    if(lList->head == NULL){
        lList->head = newNode;
        lList->tail = newNode;
        return;
    }

    if(index == 0){                 // add to front
        Node* tmp = lList->head;
        lList->head = newNode;
        newNode->next = tmp;
        tmp->prev = newNode;
        return;
    } else if (index == lList->len-1){ // add to back.
        Node* tmp = lList->tail;
        lList->tail = newNode;
        tmp->next = newNode;
        newNode->prev = tmp;
        return;
    }

    // find location in list
    Node* current = lList->head;
    int count = 1;
    while (count < index){
        current = current->next;
        count++;
    }

    // add new node
    Node* tmp = current->next;
    current->next = newNode;
    newNode->prev = current;
    newNode->next = tmp;
    if(tmp != NULL) tmp->prev = newNode;
}

void removeIdx(DoublyLinkedList* lList, int index){
    Node* current = lList->head;
    for (int count = 0; count < index; ++count) {
        current = current->next;
    }

    if(current->prev != NULL){
        current->prev->next = current->next;
    } else { lList->head = current->next; }

    if(current->next != NULL){
        current->next->prev = current->prev;
    } else { lList->tail = current->prev; }

    --(lList->len);
    free(current);
}

int find(DoublyLinkedList* lList, int data){
    int count = 0;
    Node* current = lList->head;
    while(current != NULL){
        if(current->item == data) return count;
        current = current->next;
        ++count;
    }
    return -1;
}

void printList(DoublyLinkedList* lList){
    Node* current = lList->head;
    while (current != NULL){
        printf("%d\n", current->item);
        current = current->next;
    }
}

void destroy(DoublyLinkedList* lList) {
    Node *current = lList->head;
    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
    free(lList);
}
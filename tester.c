//
// Created by Seb on 02-Jun-2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoublyLinkedList.h"

#define CMD_MAX_SIZE 128

int main(){
    DoublyLinkedList* linkedList = lListInit();
    char line [CMD_MAX_SIZE];

    while (1){
        if (fgets(line, CMD_MAX_SIZE, stdin) == NULL){
            break;
        }

        char cmd = *strtok(line, " ");

        if (cmd == 'a') {                                                             // add
            int data = strtol(strtok(NULL, " "),NULL, 10);
            int index = strtol(strtok(NULL, " "), NULL,10);
            insert(linkedList, data, index);
        } else if (cmd == 'r') {                                                      // remove
            int index = strtol(strtok(NULL, " "),NULL, 10);
            //do more here
        } else if (cmd == 'f'){                                                       // find
            int index = strtol(strtok(NULL, " "), NULL,10);
            //do more here
        } else if (cmd == 'q'){
            break;
        }
    }
    printList(linkedList);
    destroy(linkedList);
}
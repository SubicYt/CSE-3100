#include <stdio.h>


struct Node{
    int v;
    struct Node* next; //self referencing pointer
    //pointer that points to struct of the same type. Where struct behaves as like an object.
}

Node * new_node(int v){
    Node* newNode;
    newNode = malloc(sizeof(Node));
    newNode -> value = v; 
    newNode -> next = Null;
}

Node* addBeginning(Node* head, Node* newNode){
    newNode -> next = head;
    return newNode;
}

Node* findLastNode(Node* head){
    while(head -> next != NULL){
        head = head -> next;
    }
    return head;
}

Node* append(Node* head, node* newNode){
    Node* last = find_last(head);
    if(last == NULL){
        return newNode;
    }
    last -> next = newNode;
    newNode -> next = NULL;
    return newNode;
}
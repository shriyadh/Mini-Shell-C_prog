// In this file you will implement the 
// 'Function definitions'
// Recall, function definitions are the implementations
// of all of the function 'declarations' in our linkedlist.h

#include <stdio.h>
#include <stdlib.h>     // Included for malloc/free

#include "linkedlist.h"

/*
linkedlist_t* CreateLinkedListOfFiveItems(){
    
    linkedlist_t* head_one  = CreateLinkedList();
    
     
    node_t* one = (node_t*)malloc(sizeof(node_t));
    one->data = 1;
    head_one->head = one;
    
    node_t* two = (node_t*)malloc(sizeof(node_t));
    two->data = 2;
    one->next = two;

    node_t* three = (node_t*)malloc(sizeof(node_t));
    three->data = 3;
    two->next = three;
 
    node_t* four = (node_t*)malloc(sizeof(node_t));
    four->data = 4;
    three->next = four;

    node_t* five = (node_t*)malloc(sizeof(node_t));
    five->data = 5;
    four->next = five;
    five->next = NULL; 

    return head_one; // Note: you will change this line
                 //       You will change this to return
                 //       the linkedlist_t you 'malloc'
}

*/
linkedlist_t* CreateLinkedList(){
 
    linkedlist_t* head_list = (linkedlist_t*)malloc(sizeof(linkedlist_t));
    
    head_list->head = NULL;

   return head_list; // Note: you will change this line.
                 //       You will change this to return
                 //       the linkedlist_t you 'malloc'
}

void PrintLinkedList(linkedlist_t* list){
       // printing list
       node_t* iter  = list->head;
       while(iter != NULL) {
           printf(" ---->  %s\n", iter->data);
           iter = iter->next;
       }   
}

void FreeLinkedList(linkedlist_t* list){
    if(list == NULL) {
        return;
       }  
    
    node_t* current  = list->head;
    if(current == NULL) {
        free(list);
        return;
      }      
      
    
    node_t* next  = current->next;
    while(current != NULL) {
	free(current->data);
       free(current);
       current = next;
       if(current != NULL) {
         next = current->next; 
       } 
       }  
    free(list);

}


    
void AppendToLinkedList(linkedlist_t* list, char* data){
    // if list is empty

    if(list->head == NULL) {
        node_t* new_node = (node_t*)malloc(sizeof(node_t));
      //  new_node->data = data;
 	new_node->data = (char*)malloc(sizeof(char)*80);	
	strcpy(new_node->data, data);
        new_node->next = NULL; 
        list->head = new_node;  
       
     } else {
    // if list is not empty, append to end of list
        node_t* iter = list->head;    
        while(iter->next != NULL) {
            iter = iter->next;
           }
            node_t* new_node = (node_t*)malloc(sizeof(node_t));
 	    new_node->data = (char*)malloc(sizeof(char)*80);	
	    strcpy(new_node->data, data);
         

            //new_data->data = data;
            new_node->next = NULL; 
            iter->next = new_node;

}
   
}

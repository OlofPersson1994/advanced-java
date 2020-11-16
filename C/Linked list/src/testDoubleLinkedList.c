#include "testDoubleLinkedList.h"
#include <stdio.h>
#include "double_linked_list.h"

struct doubleLinkedList doubleLinkedList;
struct doubleLinkedListElement doubleLinkedListElement;

//Test and add one element
void doubleBlackBoxTestOne()
{   
    printf("Blackbox test 1\n");
    printf("Add one element to list\n");
    initDoubleLinkedList(&doubleLinkedList);
    addElementDoubleLinkedList(&doubleLinkedList, 4);
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}
//Test to add several elements
void doubleBlackBoxTestTwo()
{   
    printf("Blackbox test 2\n");
    printf("Add several elements to list\n");
    initDoubleLinkedList(&doubleLinkedList);

    for(int i = 0; i < 5; i++){
    addElementDoubleLinkedList(&doubleLinkedList, i);

    }
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}
//Test to add several element, not in order so we check the sort algorim
void doubleBlackBoxTestThree()
{   
    printf("Blackbox test 3\n");
    printf("Add several elemnts out of order to test bubbelsort\n");
    initDoubleLinkedList(&doubleLinkedList);

    for(int i = 0; i < 5; i++){
    addElementDoubleLinkedList(&doubleLinkedList, i);
    addElementDoubleLinkedList(&doubleLinkedList, 3);
    }
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}

//Test to remove the first element from list.
void doubleBlackBoxTestFour()
{   
    printf("Blackbox test 4\n");
    printf("Remove the first element in the list\n");
    initDoubleLinkedList(&doubleLinkedList);

    for(int i = 0; i < 5; i++){
    addElementDoubleLinkedList(&doubleLinkedList, i);
    }
    printDoubleLinkedList(&doubleLinkedList);
    printf("\nNow we remove one the first element\n");
    removeFirstElementDoubleLinkedList(&doubleLinkedList);
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}

//Test to remove an element from an emety list.
void doubleBlackBoxTestFive()
{   
    printf("Blackbox test 5\n");
    printf("Remove first element from an empty list\n");
    initDoubleLinkedList(&doubleLinkedList);

    removeFirstElementDoubleLinkedList(&doubleLinkedList);
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}

//Test to remove the last element from list
void doubleBlackBoxTestSix()
{   
    printf("Blackbox test 6\n");
    printf("Remove element in the end of the list \n");
    initDoubleLinkedList(&doubleLinkedList);

    addElementDoubleLinkedList(&doubleLinkedList, 4);
    addElementDoubleLinkedList(&doubleLinkedList,3);

    removeLastElementDoubleLinkedList(&doubleLinkedList);
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}
//Test to remove last element from list when the list is empty
void doubleBlackBoxTestSeven()
{   
    printf("Blackbox test 7\n");
    printf("Remove element in the end of the list in an empty list\n");
    initDoubleLinkedList(&doubleLinkedList);

    removeLastElementDoubleLinkedList(&doubleLinkedList);
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n \n");
}
//Adding one element
void doubleWhiteBoxTestOne()
{
    printf("Whitebox test 1\n");
    initDoubleLinkedList(&doubleLinkedList);
    addElementDoubleLinkedList(&doubleLinkedList, 4);
    printf("The location of head: %p \n", doubleLinkedList.first);
    printf("The value of the head is: %d \n", doubleLinkedList.first->data);
    printf("The location of last: %p \n", doubleLinkedList.last);
    printf("Below is the list printed \n");
    printDoubleLinkedList(&doubleLinkedList);
    printf("\n\n");
}
//Adding two elements and checks in the second element is in the right position and also the bubbelsort algoritm and adding serveral numbers.
void doubleWhiteBoxTestTwo()
{
    printf("Whitebox test 2\n");
    initDoubleLinkedList(&doubleLinkedList);
    addElementDoubleLinkedList(&doubleLinkedList, 7);
    addElementDoubleLinkedList(&doubleLinkedList, 4);
    printf("The location of head: %p \n", doubleLinkedList.first);
    printf("The location of next is: %p \n", doubleLinkedList.first->next);
    printf("The location of last: %p \n", doubleLinkedList.last);
    printf("The value of next is: %d \n", doubleLinkedList.first->next->data);
    printf("\n\n");
}
//Removing head
void doubleWhiteBoxTestThree()
{
    printf("Whitebox test 3\n");
    initDoubleLinkedList(&doubleLinkedList);
    addElementDoubleLinkedList(&doubleLinkedList, 6);
    addElementDoubleLinkedList(&doubleLinkedList, 5);
    addElementDoubleLinkedList(&doubleLinkedList, 7);
    addElementDoubleLinkedList(&doubleLinkedList, 8);
    printf("The location of head: %p \n", doubleLinkedList.first);
    printf("The location of next is: %p \n", doubleLinkedList.first->next);
    printf("The value of head is: %d \n", doubleLinkedList.first->data);
    printf("The location of last: %p \n", doubleLinkedList.last);
    printf("The value of last is: %d \n", doubleLinkedList.last->data);
    removeFirstElementDoubleLinkedList(&doubleLinkedList);
    printf("The new location of head is: %p \n", doubleLinkedList.first);
    printf("The new value of head is: %d \n", doubleLinkedList.first->data);
    printf("\n\n");
}

// Removing last element
void doubleWhiteBoxTestFour()
{
    printf("Whitebox test 4\n");
    initDoubleLinkedList(&doubleLinkedList);
    addElementDoubleLinkedList(&doubleLinkedList, 6);
    addElementDoubleLinkedList(&doubleLinkedList, 5);
    printf("The location of head: %p \n", doubleLinkedList.first);
    printf("The location of next is: %p \n", doubleLinkedList.first->next);
    printf("The value of next is: %d \n", doubleLinkedList.first->next->data);
    printf("The location of last: %p \n", doubleLinkedList.last);
    printf("The value of last is: %d \n", doubleLinkedList.last->data);
    removeLastElementDoubleLinkedList(&doubleLinkedList);
    printf("The location of last: %p \n", doubleLinkedList.last);
    printf("The value of last is: %d \n", doubleLinkedList.last->data);
    printf("\n\n");
}
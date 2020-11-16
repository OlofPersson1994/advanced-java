#include "testSingleLinkedList.h"
#include <stdio.h>
#include "single_linked_list.h"

struct singleLinkedList singleLinkedList;

//Test and add one element
void singleBlackBoxTestOne()
{
    printf("Blackbox test 1\n");
    printf("Add one element to list\n");
    initSingleLinkedList(&singleLinkedList);
    addElementSingleLinkedList(&singleLinkedList, 4);
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}
//Test to add several elements
void singleBlackBoxTestTwo()
{
    printf("Blackbox test 2\n");
    printf("Add several elements to list\n");
    initSingleLinkedList(&singleLinkedList);

    for (int i = 0; i < 5; i++)
    {
        addElementSingleLinkedList(&singleLinkedList, i);
    }
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}
//Test to add several element, not in order so we check the sort algorim
void singleBlackBoxTestThree()
{
    printf("Blackbox test 3\n");
    printf("Add several elemnts out of order to test bubbelsort\n");
    initSingleLinkedList(&singleLinkedList);

    for (int i = 0; i < 5; i++)
    {
        addElementSingleLinkedList(&singleLinkedList, i);
        addElementSingleLinkedList(&singleLinkedList, 3);
    }
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}

//Test to remove the first element from list.
void singleBlackBoxTestFour()
{
    printf("Blackbox test 4\n");
    printf("Remove the first element in the list\n");
    initSingleLinkedList(&singleLinkedList);

    for (int i = 0; i < 5; i++)
    {
        addElementSingleLinkedList(&singleLinkedList, i);
    }
    printSingelLinkedList(&singleLinkedList);
    printf("\nNow we remove one the first element\n");
    removeFirstElementSingleLinkedList(&singleLinkedList);
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}

//Test to remove an element from an emety list.
void singleBlackBoxTestFive()
{
    printf("Blackbox test 5\n");
    printf("Remove first element from an empty list\n");
    initSingleLinkedList(&singleLinkedList);

    removeFirstElementSingleLinkedList(&singleLinkedList);
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}

//Test to remove the last element from list
void singleBlackBoxTestSix()
{
    printf("Blackbox test 6\n");
    printf("Remove element in the end of the list \n");
    initSingleLinkedList(&singleLinkedList);

    addElementSingleLinkedList(&singleLinkedList, 5);
    addElementSingleLinkedList(&singleLinkedList, 3);

    removeLastElementSingleLinkedList(&singleLinkedList);
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}
//Test to remove last element from list when the list is empty
void singleBlackBoxTestSeven()
{
    printf("Blackbox test 7\n");
    printf("Remove element in the end of the list in an empty list\n");
    initSingleLinkedList(&singleLinkedList);

    removeLastElementSingleLinkedList(&singleLinkedList);
    printSingelLinkedList(&singleLinkedList);
    printf("\n \n");
}
//Adding one element and then checks the loaction and the value of it
void singleWhiteBoxTestOne()
{
    printf("Whitebox test 1\n");
    initSingleLinkedList(&singleLinkedList);
    addElementSingleLinkedList(&singleLinkedList, 4);
    printf("The location of head: %p \n", singleLinkedList.first);
    printf("The value of the head is: %d \n", singleLinkedList.first->data);
    printf("Below is the list printed \n");
    printSingelLinkedList(&singleLinkedList);
    printf("\n\n");
}
//Adding two elements and checks in the second element is in the right position and also the bubbelsort algoritm and adding serveral numbers.
void singleWhiteBoxTestTwo()
{
    printf("Whitebox test 2\n");
    initSingleLinkedList(&singleLinkedList);
    addElementSingleLinkedList(&singleLinkedList, 7);
    addElementSingleLinkedList(&singleLinkedList, 4);
    printf("The location of head: %p \n", singleLinkedList.first);
    printf("The location of next is: %p \n", singleLinkedList.first->next);
    printf("The value of next is: %d \n", singleLinkedList.first->next->data);
    printf("\n\n");
}
//Removing head
void singleWhiteBoxTestThree()
{
    printf("Whitebox test 3\n");
    initSingleLinkedList(&singleLinkedList);
    addElementSingleLinkedList(&singleLinkedList, 6);
    addElementSingleLinkedList(&singleLinkedList, 5);
    addElementSingleLinkedList(&singleLinkedList, 7);
    addElementSingleLinkedList(&singleLinkedList, 8);
    printf("The location of head: %p \n", singleLinkedList.first);
    printf("The location of next is: %p \n", singleLinkedList.first->next);
    printf("The value of head is: %d \n", singleLinkedList.first->data);
    removeFirstElementSingleLinkedList(&singleLinkedList);
    printf("The new location of head is: %p \n", singleLinkedList.first);
    printf("The new value of head is: %d \n", singleLinkedList.first->data);
    printf("\n\n");
}

// Removing last element
void singleWhiteBoxTestFour()
{
    printf("Whitebox test 4\n");
    initSingleLinkedList(&singleLinkedList);
    addElementSingleLinkedList(&singleLinkedList, 6);
    addElementSingleLinkedList(&singleLinkedList, 5);
    printf("The location of head: %p \n", singleLinkedList.first);
    printf("The location of next is: %p \n", singleLinkedList.first->next);
    printf("The value of next is: %d \n", singleLinkedList.first->next->data);
    removeLastElementSingleLinkedList(&singleLinkedList);
    printSingelLinkedList(&singleLinkedList);
    printf("\n\n");
}

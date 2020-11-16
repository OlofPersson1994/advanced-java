#include <stdio.h>
#include <stdlib.h>
#include "testSingleLinkedList.h"
#include "testDoubleLinkedList.h"
#include "single_linked_list.h"
#include "double_linked_list.h"

void app_main()
{
    printf("SINGLE LINKEDLIST TEST \n");

    singleBlackBoxTestOne();
    singleBlackBoxTestTwo();
    singleBlackBoxTestThree();
    singleBlackBoxTestFour();
    singleBlackBoxTestFive();
    singleBlackBoxTestSix();
    singleBlackBoxTestSeven();
    singleWhiteBoxTestOne();
    singleWhiteBoxTestTwo();
    singleWhiteBoxTestThree();
    singleWhiteBoxTestFour();

    printf("\nDOUBLE LINKEDLIST TEST \n");

    doubleBlackBoxTestOne();
    doubleBlackBoxTestTwo();
    doubleBlackBoxTestThree();
    doubleBlackBoxTestFour();
    doubleBlackBoxTestFive();
    doubleBlackBoxTestSix();
    doubleBlackBoxTestSeven();

    doubleWhiteBoxTestOne();
    doubleWhiteBoxTestTwo();
    doubleWhiteBoxTestThree();
    doubleWhiteBoxTestFour();

    /*
    initSingleLinkedList(&singleLinkedList);
    initDoubleLinkedList(&doubleLinkedList);

    addElementSingleLinkedList(&singleLinkedList, 7);
    addElementSingleLinkedList(&singleLinkedList, 6);

    resetSingelLinkedList(&singleLinkedList);

    removeFirstElementSingleLinkedList(&singleLinkedList);

    printSingelLinkedList(&singleLinkedList); */
}

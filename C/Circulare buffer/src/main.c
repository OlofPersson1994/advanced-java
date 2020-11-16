#include <stdio.h>
#include <stdlib.h>
#include <esp32/rom/ets_sys.h>
#include "circular_buffer.h"
#include <limits.h>

/*
 * Change the value of BUFFER_SIZE if you want to change the size of the buffer. 
 */
#define BUFFER_SIZE 4

struct circularBuffer buffer;

void blackBoxTestOne();
void blackBoxTestTwo();
void blackBoxTestThree();
void blackBoxTestFour();
void blackBoxTestFive();
void blackBoxTestSix();
void blackBoxTestSeven();
void blackBoxTestEight();
void blackBoxTestNine();

void whiteBoxTestinitCirkulerBuffer();
void whiteBoxTestaddElementOne();
void whiteBoxTestaddElementTwo();
void whiteBoxTestaddElemetnThree();
void whiteBoxTestaddElemetnFour();
void whiteBoxTestRemoveValueOne();
void whiteBoxTestRemoveValueTwo();
void whiteBoxTestRemoveValueThree();
void whiteBoxTestRemoveHeadOne();
void whiteBoxTestRemoveHeadTwo();
void whiteBoxTestRemoveHeadThree();
void whiteBoxTestRemoveHeadFour();

void app_main()
{

    // Some code to help you get started
    //struct circularBuffer buffer;

    int *buffer_data = (int *)malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);

    blackBoxTestOne();
    blackBoxTestTwo();
    blackBoxTestThree();
    blackBoxTestFour(); 
    blackBoxTestFive();
    blackBoxTestSix();
    blackBoxTestSeven(); 
    blackBoxTestEight(); 
    blackBoxTestNine(); 

    whiteBoxTestinitCirkulerBuffer(); 
    whiteBoxTestaddElementOne();  
    whiteBoxTestaddElementTwo(); 
    whiteBoxTestaddElemetnThree(); 
    whiteBoxTestaddElemetnFour(); 
    whiteBoxTestRemoveValueOne(); 
    whiteBoxTestRemoveValueTwo(); 
    whiteBoxTestRemoveValueThree(); 
    whiteBoxTestRemoveHeadOne();
    whiteBoxTestRemoveHeadTwo();
    whiteBoxTestRemoveHeadThree();
    whiteBoxTestRemoveHeadFour();

    free(buffer_data);
}

void blackBoxTestOne()
{

    printf("\nBlack box test 1 \n");

    addElement(&buffer, 1);
    removeHead(&buffer);
    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestTwo()
{

    printf("\nBlack box test 2 \n");

    addElement(&buffer, 1);
    addElement(&buffer, 2);
    removeValue(&buffer, 1);
    removeValue(&buffer, 2);
    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestThree()
{

    printf("\nBlack box test 3 \n");

    for (int i = 0; i <= BUFFER_SIZE; i++)
    {

        addElement(&buffer, i);
    }
    for (int i = 0; i <= BUFFER_SIZE; i++)
    {

        removeValue(&buffer, i);
    }
    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestFour()
{

    printf("\nBlack box test 4 \n");

    for (int i = 0; i <= BUFFER_SIZE + 1; i++)
    {
        addElement(&buffer, i);
    }

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestFive()
{
    printf("\nBlack box test 5 \n");

    for (int i = 0; i < BUFFER_SIZE + 1; i++)
    {

        addElement(&buffer, i);
        removeHead(&buffer);
    }

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestSix()
{
    printf("\nBlack box test 6 \n");

    if (contains(&buffer, 1) == INT_MIN)
    {

        printf("Black box 6 retunerar INT_MIN \n");
    }
    else
    {
        printf("Black box 6 retunerar inte INT_MIN \n");
    }
    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestSeven()
{
    printf("\nBlack box test 7 \n");

    addElement(&buffer, 1);
    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestEight()
{
    printf("\nBlack box test 8 \n");

    addElement(&buffer, 1);
    addElement(&buffer, 2);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void blackBoxTestNine()
{
    printf("\nBlack box test 9 \n");

    for (int i = 0; i <= BUFFER_SIZE; i++)
    {
        addElement(&buffer, i);
    }
    if (contains(&buffer, BUFFER_SIZE) == BUFFER_SIZE)
    {
        printf("Bufferten innehåller BUFFER_SIZE\n");
    }
    else
    {
        printf("Bufferten innehåller inte BUFFER_SIZE\n");
    }

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestinitCirkulerBuffer()
{

    printf("\nWhite box test 1 \n");

    if (buffer.maxLength == BUFFER_SIZE)
    {

        printf("buffer.maxLengt är lika stor som BUFFER_SIZE\n");
    }
    if (buffer.head == 0)
    {

        printf("Headern är på plats 0\n");
    }
    if (buffer.tail == 0)
    {

        printf("Tailen är på plats 0\n");
    }

    else
    {

        printf("Dags att göra om koden Olof\n");
    }

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestaddElementOne()
{
    printf("\nWhite box test 2 \n");

    addElement(&buffer, 1);
    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestaddElementTwo()
{
    printf("\nWhite box test 3 \n");

    buffer.head = 1;
    buffer.tail = 1;

    buffer.booleanIsBufferEmpty = 0;

    addElement(&buffer, 1);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestaddElemetnThree()
{
    printf("\nWhite box test 4 \n");

    buffer.data[buffer.head] = 1;

    buffer.booleanIsBufferEmpty = 0;

    addElement(&buffer, 7);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestaddElemetnFour()
{
    printf("\nWhite box test 5 \n");

    buffer.booleanIsBufferEmpty = 0;

    for (int i = 0; i < BUFFER_SIZE; i++)
    {

        buffer.data[buffer.tail + i] = i;
    }

    buffer.tail = BUFFER_SIZE - 1;

    addElement(&buffer, BUFFER_SIZE);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveValueOne()
{
    printf("\nWhite box test 6 \n");

    buffer.data[buffer.tail] = 7;
    buffer.booleanIsBufferEmpty = 0;

    removeValue(&buffer, 7);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveValueTwo()
{
    printf("\nWhite box test 7 \n");

    buffer.booleanIsBufferEmpty = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {

        buffer.data[buffer.tail + i] = i;
    }

    buffer.tail = BUFFER_SIZE - 1;

    removeValue(&buffer, 0);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveValueThree()
{
    printf("\nWhite box test 7 \n");

    if (removeValue(&buffer, 1) == INT_MIN)
    {
        printf("Bufferten är redan tom");
    }
    else
    {
        printf("Bufferten var inte tom och du lyckades ta bort ett värde");
    }
    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveHeadOne()
{
    printf("\nWhite box test 8 \n");

    buffer.booleanIsBufferEmpty = 0;
    buffer.data[buffer.tail] = 1;

    removeHead(&buffer);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveHeadTwo()
{
    printf("\nWhite box test 9 \n");
    buffer.booleanIsBufferEmpty = 0;
    buffer.data[buffer.tail] = 1;
    buffer.tail = 1;
    buffer.data[buffer.tail] = 2;

    removeHead(&buffer);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveHeadThree()
{
    printf("\nWhite box test 10 \n");
    buffer.booleanIsBufferEmpty = 0;
    buffer.data[buffer.tail] = 1;
    buffer.tail = 1;
    buffer.data[buffer.tail] = 2;
    buffer.tail = 2;
    buffer.data[buffer.tail] = 3;

    removeHead(&buffer);

    printBuffer(&buffer);

    printf("\n\n");

    resetBuffer(&buffer);
}

void whiteBoxTestRemoveHeadFour()
{
    printf("\nWhite box test 11 \n");

    if (removeHead(&buffer) == INT_MIN)
    {
        printf("Din buffer är redan tom\n");
    }
    else
    {
        printf("Bufferten var inte tom och du lyckades ta bort ett värde \n");
    }
    printf("\n\n");

    resetBuffer(&buffer);
}

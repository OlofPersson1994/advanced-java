#include<stdlib.h>
#include<limits.h>
#include <stdio.h>
#include"double_linked_list.h"


int addElementDoubleLinkedList(struct doubleLinkedList *list, int value){

  struct doubleLinkedListElement *newElement = (struct doubleLinkedListElement *)malloc(sizeof(struct doubleLinkedListElement));

  struct doubleLinkedListElement *temp;
  struct doubleLinkedListElement *tempOneBack;


  // Första gången någont läggs till i listan.
  if (list->first == NULL)
  {
    list->first = newElement;
    list->last = newElement;
    newElement->data = value;
    newElement->next = NULL;
    newElement->previous = NULL;
    
    return value;
  }
  else
  {
    temp = list->first;
    tempOneBack = list->first;

    while (temp->next != NULL)
    {

      temp = temp->next;
      tempOneBack = temp->previous;
    }

    temp->next = newElement;
    list->last = newElement;
    newElement->next = NULL;
    newElement->previous = tempOneBack;
    newElement->data = value;
  
    bubbleSorting(list);
    return value;
  }

  return INT_MIN;
  
} 

void initDoubleLinkedList(struct doubleLinkedList* list) {
  list->first = NULL;
  list->last = NULL;
}

int removeFirstElementDoubleLinkedList(struct doubleLinkedList* list){
  struct doubleLinkedListElement *removeFirst = list->first;
  struct doubleLinkedListElement *removeMalocFirst = list->first;
  int returnValue;

  // När det inte finns något att ta bort
  if (list->first == NULL)
  {
    return INT_MIN;
  }
  // När det bara finns ett element att ta bort
  if (removeFirst->next == NULL)
  {
    returnValue = list->first->data;
    free(list->first);
    list->first = NULL;
    list->last = NULL;

    return returnValue;
  }
  // När det finns mer än ett element i listan.
  if (removeFirst->next != NULL)
  {
    list->first = list->first->next;

    free(removeMalocFirst);

    return list->first->data;
  }

  return INT_MIN;
} 

int removeLastElementDoubleLinkedList(struct doubleLinkedList* list) 
{
  struct doubleLinkedListElement *removeLast = list->first;
  struct doubleLinkedListElement *secondLastNode = list->first;
  int returnValue;

  // När listan är tom från början.
  if (list->first == NULL)
  {
    return INT_MIN;
  }

  // När listan bara har ett element kvar.
  if (removeLast->next == NULL)
  {
    returnValue = list->first->data;
    free(list->first);
    list->first = NULL;
    list->last = NULL;

    return returnValue;
  }

  // När det finns flera elment i listan.
  else
  {
    while (removeLast->next != NULL)
    {
      secondLastNode = removeLast;
      removeLast = removeLast->next;
    }
    list->last = secondLastNode;
    secondLastNode->next = NULL;
    free(removeLast);
    return list->last->data;
  }
}

void printDoubleLinkedList(struct doubleLinkedList *list)
{
  struct doubleLinkedListElement *print = list->first;

  while (print != NULL)
  {

    printf("%d \n", print->data);
    print = print->next;
  }
}

void bubbleSorting(struct doubleLinkedList *list)
{
  int swapped;
  struct doubleLinkedListElement *ptr1;
  struct doubleLinkedListElement *lptr = NULL;

  /* Bubbelsort inspirerd from geeksforgeeks */
  if (list == NULL)
    return;

  do
  {
    swapped = 0;
    ptr1 = list->first;

    while (ptr1->next != lptr)
    {
      if (ptr1->data > ptr1->next->data)
      {
        swaping(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void swaping(struct doubleLinkedListElement *valueA, struct doubleLinkedListElement *valueB)

{
  int temp = valueA->data;
  valueA->data = valueB->data;
  valueB->data = temp;
}

void resetDoubleLinkedList(struct doubleLinkedList *list)
{
  struct doubleLinkedListElement *remove = list->first;
  struct doubleLinkedListElement *ptr = list->first;

  while (remove != NULL)
  {
    ptr = ptr->next;
    free(remove);
    remove = NULL;
    remove = ptr;
  }
  list->first = NULL;
  list->last = NULL;
}

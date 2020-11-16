#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "single_linked_list.h"

int addElementSingleLinkedList(struct singleLinkedList *list, int value)
{
  struct singleLinkedListElement *newElement = (struct singleLinkedListElement *)malloc(sizeof(struct singleLinkedListElement));

  struct singleLinkedListElement *temp;

  if (list->first == NULL)
  {
    list->first = newElement;
    newElement->data = value;
    newElement->next = NULL;

    return value;
  }
  else
  {
    temp = list->first;

    while (temp->next != NULL)
    {

      temp = temp->next;
    }

    temp->next = newElement;
    newElement->data = value;
    newElement->next = NULL;
    bubbleSort(list);
    return value;
  }

  return INT_MIN;
}

void initSingleLinkedList(struct singleLinkedList *list)
{
  list->first = NULL;
}

int removeFirstElementSingleLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *removeFirst = list->first;
  struct singleLinkedListElement *removeMalocFirst = list->first;
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

int removeLastElementSingleLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *removeLast = list->first;
  struct singleLinkedListElement *secondLastNode = list->first;
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

    secondLastNode->next = NULL;
    free(removeLast);
    return list->first->data;
  }
}

void printSingelLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *print = list->first;

  while (print != NULL)
  {

    printf("%d \n", print->data);
    print = print->next;
  }
}

void bubbleSort(struct singleLinkedList *list)
{
  int swapped;
  struct singleLinkedListElement *ptr1;
  struct singleLinkedListElement *lptr = NULL;

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
        swap(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void swap(struct singleLinkedListElement *valueA, struct singleLinkedListElement *valueB)
{
  int temp = valueA->data;
  valueA->data = valueB->data;
  valueB->data = temp;
}

void resetSingelLinkedList(struct singleLinkedList *list)
{
  struct singleLinkedListElement *remove = list->first;
  struct singleLinkedListElement *ptr = list->first;

  while (remove != NULL)
  {
    ptr = ptr->next;
    free(remove);
    remove = NULL;
    remove = ptr;
  }
  list->first = NULL;
}


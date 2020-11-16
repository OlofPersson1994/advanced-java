#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"

void initCircularBuffer(struct circularBuffer *bufferPtr, int *data, int maxLength)
{
  bufferPtr->data = data;
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
  bufferPtr->maxLength = maxLength;
  bufferPtr->booleanIsBufferEmpty = 1;
}

int contains(struct circularBuffer *bufferPtr, int value)
{

  int tempPos = bufferPtr->head;

  if (bufferPtr->head != bufferPtr->maxLength)
  {

    for (int i = bufferPtr->head; i < bufferPtr->maxLength || i <= bufferPtr->tail; i++)
    {

      if (bufferPtr->data[i] == value)
      {

        bufferPtr->head = tempPos;
        return value;
      }
      if (i == bufferPtr->maxLength - 1)
      {

        bufferPtr->head = 0;

        for (int p = bufferPtr->head; p <= bufferPtr->tail; p++)
        {

          if (bufferPtr->data[p] == value)
          {

            bufferPtr->head = tempPos;
            return value;
          }
        }
      }
    }
  }
  if (bufferPtr->head == bufferPtr->maxLength)
  {

    if (bufferPtr->data[bufferPtr->head] == value)
    {

      bufferPtr->head = 0;

      bufferPtr->head = tempPos;
      return value;
    }
  }
  bufferPtr->head = tempPos;

  return INT_MIN;
}

int addElement(struct circularBuffer *bufferPtr, int value)
{

  int returnValue = INT_MIN;

  if (bufferPtr->booleanIsBufferEmpty == 1)
  {

    bufferPtr->head = 0;
    bufferPtr->tail = 0;

    bufferPtr->data[bufferPtr->tail] = value;

    bufferPtr->booleanIsBufferEmpty = 0;

    returnValue = value;


    return value;
  }

  if (bufferPtr->tail == bufferPtr->head && bufferPtr->booleanIsBufferEmpty == 0)
  {

    bufferPtr->tail++;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;


    return value;
  }

  if (bufferPtr->tail == bufferPtr->maxLength - 1 && bufferPtr->booleanIsBufferEmpty == 0 && bufferPtr->head == 0)
  {

    bufferPtr->tail = 0;
    bufferPtr->head++;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;

    

    return value;
  }
  if (bufferPtr->tail == bufferPtr->maxLength - 1 && bufferPtr->booleanIsBufferEmpty == 0)
  {

    bufferPtr->tail = 0;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;

    

    return value;
  }

  if (bufferPtr->head == bufferPtr->maxLength - 1 && bufferPtr->booleanIsBufferEmpty == 0)
  {

    bufferPtr->tail++;
    bufferPtr->head = 0;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;


    return value;
  }

  if ((bufferPtr->tail != bufferPtr->maxLength - 1) && (bufferPtr->head == 0))
  {

    bufferPtr->tail++;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;


    return value;
  }
  else
  {

    bufferPtr->head++;
    bufferPtr->tail++;
    bufferPtr->data[bufferPtr->tail] = value;

    returnValue = value;


    return value;
  }
  return returnValue;
}

int removeHead(struct circularBuffer *bufferPtr)
{

  int returnValue;

  if (bufferPtr->booleanIsBufferEmpty == 1)
  {

    return INT_MIN;
  }
  else
  {

    if (bufferPtr->head == bufferPtr->maxLength)
    {

      returnValue = bufferPtr->data[bufferPtr->head];

      bufferPtr->head = 0;

      return returnValue;
    }
    else
    {

      returnValue = bufferPtr->data[bufferPtr->head];
      bufferPtr->head++;
      if (bufferPtr->head == bufferPtr->tail + 1)
      {

        bufferPtr->booleanIsBufferEmpty = 1;
        bufferPtr->head--;
      }
      return returnValue;
    }
  }
}

void printBuffer(struct circularBuffer *bufferPtr)
{
  int tempPos = bufferPtr->head;

  printf("The head is at posision: %d \n", bufferPtr->head);
  printf("The tail is at posison: %d \n", bufferPtr->tail);

  if (bufferPtr->booleanIsBufferEmpty == 1)
  {

    printf("Buffern är tom \n");
  }

  if (bufferPtr->head != bufferPtr->maxLength && bufferPtr->booleanIsBufferEmpty == 0)
  {

    for (int i = bufferPtr->head; i < bufferPtr->maxLength || i <= bufferPtr->tail; i++)
    {

      printf("Value: %d på plats: %d \n", bufferPtr->data[i], i);
      bufferPtr->head = tempPos;
      if (i == bufferPtr->tail)
      {
        bufferPtr->head = tempPos;
        break;
      }

      if (i == bufferPtr->maxLength - 1)
      {

        bufferPtr->head = 0;

        for (int p = bufferPtr->head; p <= bufferPtr->tail; p++)
        {

          printf("Value: %d på plats: %d \n", bufferPtr->data[p], p);
          bufferPtr->head = tempPos;
        }
      }
    }
  }
  if (bufferPtr->head == bufferPtr->maxLength && bufferPtr->booleanIsBufferEmpty == 0)
  {

    printf("Value: %d på plats %d \n", bufferPtr->data[bufferPtr->head], bufferPtr->head);

    bufferPtr->head = 0;

    for (int k = bufferPtr->head; k <= bufferPtr->tail; k++)
    {

      printf("Value: %d på plats %d \n", bufferPtr->data[k], k);
    }
    bufferPtr->head = tempPos;
  }
  bufferPtr->head = tempPos;
}

int removeValue(struct circularBuffer *bufferPtr, int value)

{
  int tempArray[bufferPtr->maxLength];
  int countIndex = 0;
  int newSizeOfArray = -1;
  int tempHeadPos = bufferPtr->head;

  if (bufferPtr->head < bufferPtr->tail)
  {
    for (int i = bufferPtr->head; i <= bufferPtr->tail; i++)
    {

      if (bufferPtr->data[i] != value)
      {
        tempArray[countIndex] = bufferPtr->data[i];

        countIndex++;
        newSizeOfArray++;
      }
    }
  }

  if (bufferPtr->head > bufferPtr->tail)
  {

    for (int i = bufferPtr->head; i < bufferPtr->maxLength; i++)
    {

      if (bufferPtr->data[i] != value)
      {

        tempArray[countIndex] = bufferPtr->data[i];

        countIndex++;
        newSizeOfArray++;
      }
    }

    bufferPtr->head = 0;

    for (int k = bufferPtr->head; k <= bufferPtr->tail; k++)
    {
      if (bufferPtr->data[k] != value)
      {
        tempArray[countIndex] = bufferPtr->data[k];

        countIndex++;
        newSizeOfArray++;
      }
    }
    bufferPtr->head = tempHeadPos;
  }

  if ((bufferPtr->tail) == 0 && (bufferPtr->head == 0))
  {

    if (bufferPtr->booleanIsBufferEmpty == 0)
    {

      if (bufferPtr->data[bufferPtr->tail] != value)
      {

        tempArray[countIndex] = bufferPtr->data[bufferPtr->tail];

        countIndex++;

        newSizeOfArray++;
      }
    }
  }

  if ((countIndex >= 0) && (bufferPtr->booleanIsBufferEmpty == 0))
  {

    for (int i = 0; i < countIndex; i++)
    {

      bufferPtr->data[i] = tempArray[i];
      bufferPtr->booleanIsBufferEmpty = 0;
    }
    

    bufferPtr->head = 0;

    bufferPtr->tail = newSizeOfArray;
  }
  if (countIndex == 0)
  {

    bufferPtr->booleanIsBufferEmpty = 1;
  }

  if ((countIndex == 0) && (bufferPtr->booleanIsBufferEmpty == 1))
  {
    bufferPtr->head = 0;
    bufferPtr->tail = 0;

    return INT_MIN;
  }

  return value;
}

void resetBuffer(struct circularBuffer *bufferPtr)
{

  bufferPtr->booleanIsBufferEmpty = 1;
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
}

#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"
#include <math.h>
#include "pins.h"

//initiates the buffer. Sets it to empty with empty = 1
void initCircularBuffer(struct circularBuffer *bufferPtr, int *data, int maxLength)
{
  bufferPtr->data = data;
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
  bufferPtr->maxLength = maxLength;
  bufferPtr->empty = 1;
}
/*
Goes from pointer head to tail and checks the data on the index. Compares that data to the value. 
If the data == value returns value else returns INT_MIN.
*/
int contains(struct circularBuffer *bufferPtr, int value)
{
  int tempPointer = bufferPtr->head;
  if (bufferPtr->empty)
  {
    printf("Buffer is empty\n");
  }
  else
  {
    do
    {
      if (bufferPtr->data[tempPointer] == value)
      {
        return value;
      }

      tempPointer++;
      if (tempPointer == (bufferPtr->tail + 1))
      {
        break;
      }
      if (tempPointer >= bufferPtr->maxLength)
      {
        tempPointer = 0;
      }

    } while (tempPointer != (bufferPtr->tail + 1));
  }

  return INT_MIN;
}

/*
Adds values to the buffer. 
If tail pointer becomes maxLength or bigger sets tail pointer to 0,
If tail pointer becomes head pointer moves head pointer on idex forward
When head pointer becomes maxLength or bigger sets head pointer to 0.
Returns value if succesful or INT_MIN if unsuccesful.
*/
int addElement(struct circularBuffer *bufferPtr, int value)
{
  int dataValue = value;
  int tempIndex;

  if (bufferPtr->empty)
  {
    tempIndex = bufferPtr->tail;
  }
  else
  {
    tempIndex = bufferPtr->tail + 1;
  }

  if (tempIndex >= bufferPtr->maxLength)
  {
    tempIndex = 0;
  }
  if (!bufferPtr->empty)
  {
    if (tempIndex == bufferPtr->head)
    {
      bufferPtr->head++;
    }
  }

  if (bufferPtr->head >= bufferPtr->maxLength)
  {
    bufferPtr->head = 0;
  }

  bufferPtr->tail = tempIndex;
  bufferPtr->data[bufferPtr->tail] = value;

  if (bufferPtr->data[bufferPtr->tail] == value)
  {
    dataValue = value;
  }
  else
  {
    dataValue = INT_MIN;
  }
  bufferPtr->empty = 0;

  return dataValue;
}

/*
Removes all values of a specific type
Creats a new array.
Compares data in the buffert with the value to remove.
If data != value put it in the new array. When all values have been checked
set head pointer to index 0 and tail pointer to the last index with data.
The new array becomes the buffer.
If all data is removed in the buffer set both pointer to 0 in the new array and empty = 1 (true).
*/
int removeValue(struct circularBuffer *bufferPtr, int value)
{
  int tempHeadPointer = bufferPtr->head;
  int indexTemp = 0;
  int tempArray[bufferPtr->maxLength];
  do
  {
    if (bufferPtr->data[tempHeadPointer] == value)
    {
      tempHeadPointer++;
    }
    else
    {
      tempArray[indexTemp] = bufferPtr->data[tempHeadPointer];

      indexTemp++;
      tempHeadPointer++;
    }

    if (tempHeadPointer == (bufferPtr->tail + 1))
    {
      break;
    }
    if (tempHeadPointer >= bufferPtr->maxLength)
    {
      tempHeadPointer = 0;
    }
  } while (tempHeadPointer != (bufferPtr->tail + 1));

  if (indexTemp == 0)
  {
    bufferPtr->empty = 1;
    bufferPtr->head = 0;
    bufferPtr->tail = 0;
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      bufferPtr->data[i] = tempArray[i];
    }
    bufferPtr->head = 0;
    bufferPtr->tail = indexTemp - 1;
  }
  if (indexTemp == tempHeadPointer)
  {
    return INT_MIN;
  }
  else
  {
    return value;
  }
  return 0;
}

/*
Removes the data on head pointer
Increments header pointer once. If head pointer is bigger or equals to maxLength 
sets head pointer to 0 (start of buffer).
If head pointer goes past tail pointer decrease by 1 and set buffer as empty == 1;
Return INT_MIN if buffert is empty or return data data that was removed.
*/
int removeHead(struct circularBuffer *bufferPtr)
{
  int removedValue = bufferPtr->data[bufferPtr->head];
  if (bufferPtr->empty)
  {
    return INT_MIN;
  }

  bufferPtr->head++;
  if (bufferPtr->head == (bufferPtr->tail + 1))
  {
    bufferPtr->empty = 1;
    bufferPtr->head--;
  }
  if (bufferPtr->head >= (bufferPtr->maxLength))
  {
    bufferPtr->head = 0;
  }

  return removedValue;
}

/*
Prints the buffert, head pointer and tail pointer position. 
Print buffert from head to tail.
If head pointer is bigger or equals to maxLength 
sets head pointer to 0 (start of buffer).
*/
void printBuffer(struct circularBuffer *bufferPtr)
{
  int tempPointer = bufferPtr->head;
  if (bufferPtr->empty)
  {
    printf("Header position: %d\n", bufferPtr->head);
    printf("Tail position: %d\n", bufferPtr->tail);
    printf("Buffer is empty\n");
  }
  else
  {
    printf("Head position: %d\n", bufferPtr->head);
    printf("Tail position: %d\n", bufferPtr->tail);

    do
    {
      printf("Index: %d Data: %d\n", tempPointer, bufferPtr->data[tempPointer]);
      tempPointer++;
      if (tempPointer == (bufferPtr->tail + 1))
      {
        break;
      }
      if (tempPointer >= bufferPtr->maxLength)
      {
        tempPointer = 0;
      }

    } while (tempPointer != (bufferPtr->tail + 1));
  }
}
//counts how many values there is in the buffer
int containsNumberOfValues(struct circularBuffer *bufferPtr)
{
  int tempHeadPointer = bufferPtr->head;
  int indexTemp = 0;
  if (bufferPtr->empty)
  {
    return 0;
  }

  do
  {
    tempHeadPointer++;
    indexTemp++;
    if (tempHeadPointer == (bufferPtr->tail + 1))
    {
      break;
    }
    if (tempHeadPointer >= bufferPtr->maxLength)
    {
      tempHeadPointer = 0;
    }

  } while (tempHeadPointer != (bufferPtr->tail + 1));
  return indexTemp;
}
//adds all values in the buffer to one sum
uint32_t addAllValuesInBuffer(struct circularBuffer *bufferPtr)
{
  int tempHeadPointer = bufferPtr->head;
  uint32_t sum = 0;
  if (bufferPtr->empty)
  {
    return 0;
  }

  do
  {
    sum += bufferPtr->data[tempHeadPointer];
    tempHeadPointer++;
    if (tempHeadPointer == (bufferPtr->tail + 1))
    {
      break;
    }
    if (tempHeadPointer >= bufferPtr->maxLength)
    {
      tempHeadPointer = 0;
    }

  } while (tempHeadPointer != (bufferPtr->tail + 1));
  return sum;
}

uint32_t addAllValuesInBufferMinusValue(struct circularBuffer *bufferPtr, int value)
{
  int tempHeadPointer = bufferPtr->head;
  uint32_t sum = 0;
  if (bufferPtr->empty)
  {
    return 0;
  }

  do
  {
    sum += (uint32_t)pow((double)(bufferPtr->data[tempHeadPointer] - value), 2);
    tempHeadPointer++;
    if (tempHeadPointer == (bufferPtr->tail + 1))
    {
      break;
    }
    if (tempHeadPointer >= bufferPtr->maxLength)
    {
      tempHeadPointer = 0;
    }

  } while (tempHeadPointer != (bufferPtr->tail + 1));
  return sum;
}

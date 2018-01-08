#ifndef _MY_INT_FUNCTIONS_H_
#define _MY_INT_FUNCTIONS_H_
#include "Key.h"
#include "stdio.h"
#include "stdlib.h"
#define SAME = 0;
#define NOT_SAME = -1;

/**
 * @brief clone an int
 */
void* cloneInt(const void* i)
{
    int *clonedInt = malloc(sizeof(int));
    *clonedInt = *(int*)i;
}

/**
 * @brief free an int
 */
void freeInt(void* i)
{
    if (i != NULL)
    {
        free(i);
    }
}


/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to an int
 * @return number between 0-(tableSize-1)
 */
int intFcn (const void* key, size_t tableSize)
{
    int hashKey = *((int*)key);
    int hash = hashKey % tableSize;
    if (hash < 0)
    {
        hash = tableSize + hash;
    }
    return hash;


}
/**
 * @brief print a string
 *  assuming key pointer to an int
 *
 */
void intPrint (const void* key)
{
    printf("%d", *(int*)key);
}
/**
 *  intCompare - pointer to int comparison function:
 * @brief compare 2 ints
 *   returns zero int if both ints are equal, otherwise
 *   returns non-zero.
 *
 */
int intCompare (const void* i, const void* j)
{
    if (i == j)
    {
        return 0;
    }
    return -1;
}

#endif // _MY_INT_FUNCTIONS_H_

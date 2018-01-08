#ifndef _MY_STR_FUNCTIONS_H_
#define _MY_STR_FUNCTIONS_H_

#include "stdio.h"
#include "stdlib.h"
#define NOT_SAME = -1;
#define SAME = 0;

/**
 * @brief clone a string
 */
void* cloneStr(const void*  s)
{
    char *clonedString = malloc(sizeof(char));
    *clonedString = *(char*)s;
}

/**
 * @brief free an string
 */
void freeStr(void* s)
{
    free(s);
}


/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to string
 * @return number between 0-(tableSize-1)

 */
int strFcn (const void*  s, size_t tableSize)
{
    int* key = (int*) s;
    int hash = *key % tableSize;
    if (hash < 0)
    {
        hash = tableSize + hash;
    }
    return hash;
}
/**
 * @brief print a string
 *  assuming key pointer to string
 *
 */
void strPrint (const void*  s)
{
    printf("%p", s);
}
/**
 *  strCompare - pointer to int comparison function:
 * @brief compare 2 strings
 *   returns zero int if both strings are equal, otherwise
 *   returns non-zero.
 */
int strCompare (const char* string1, const char* string2)
{
    int i = 0;
    for (i; string1[i] != '\0'; i++)
    {
        for (i; string2[i] != '\0'; i++)
        {
            if (string1[i] != string2[i])
            {
                return -2;
            }
        }
    }
    return 0;
}

#endif // _MY_STR_FUNCTIONS_H_

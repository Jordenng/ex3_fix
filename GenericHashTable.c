#ifndef _GENERIC_HASH_TABLE_
#define _GENERIC_HASH_TABLE_
#include <stdbool.h>
#include <glob.h>
#include "Key.h"
#include "stdlib.h"
#include "TableErrorHandle.h"
#include "stdio.h"

typedef void* DataP;
typedef struct Table* TableP;
typedef const void* ConstKeyP;
/**
 *
 */
typedef struct Object *ObjectP;

/**
 * @brief print function
 *
 */
typedef void(*PrintDataFcn)(const void* data);
/**
 *
 */
typedef struct Table
{
    size_t tableSize;
    CloneKeyFcn cloneKey;
    FreeKeyFcn freeKey;
    HashFcn hfun;
    PrintKeyFcn printKeyFun;
    PrintDataFcn printDataFun;
    ComparisonFcn fcomp;
    ObjectP *numOfObject;
    DataP data;
    size_t curSize;

} Table;

/**
 *
 */
typedef struct Object
{
    DataP data;
    ConstKeyP key;
} Object;


/**
 * @brief Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */

TableP createTable(size_t tableSize, CloneKeyFcn cloneKey, FreeKeyFcn freeKey,
                   HashFcn hfun, PrintKeyFcn printKeyFun, PrintDataFcn printDataFun,
                   ComparisonFcn fcomp)
{
    TableP table;
    table = malloc(sizeof(struct Table));

    table->tableSize = tableSize;
    table->printDataFun = printDataFun;
    table->hfun = hfun;
    table->cloneKey = cloneKey;
    table->fcomp = fcomp;
    table->freeKey = freeKey;
    table->printKeyFun = printKeyFun;
    table->curSize = 1;

    if (table == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    if (table->tableSize == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    for (unsigned int i = 0; i < table->tableSize; i++)
    {
        Object* object = (Object*)malloc(sizeof(struct Object));
        table->numOfObject[i] = object;
    }

    return table;
}
/**
 *
 * @param table
 */
static void rehash(const TableP table)
{
    ObjectP* object = (Object*)malloc(sizeof(Object) * table->tableSize * 2);
    for (unsigned int i = 0; i < table->tableSize; i++)
    {
        object[i*2] = table->numOfObject[i];
    }
    table->curSize *= 2;
    table->tableSize *= 2;

    free(table->numOfObject);
    table->numOfObject = object;
}

/**
 *
 * @param table
 * @param key
 * @return
 */
int findCell(const TableP table, const void* key)
{
    int i = 0;
    int cell = table->hfun(key, table->curSize) * table->curSize;
    for (cell; cell < cell + table->curSize; cell++)
    {
        if (table->fcomp(table->numOfObject[cell]->key, key))
        {
            i = cell;
            break;
        }
        if (i != cell)
        {
            rehash(table);
        }
    }
    return i;
}
/**
 * @brief Insert an object to the table with key.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return true. Otherwise (an error occured) return false;
 */
int insert(const TableP table, const void* key, DataP object)
{
    void *copy = table->cloneKey(key);
    if (copy == NULL)
    {
        reportError(MEM_OUT);
    }
    int cell = findCell(table, key);
    table->numOfObject[cell]->key = key;
    table->numOfObject[cell]->data = object;
    return true;
}


/**
 * @brief remove an data from the table.
 * If everything is OK, return the pointer to the ejected data. Otherwise return NULL;
 */
DataP removeData(TableP table, const void* key)
{
    DataP data = NULL;
    if (key == NULL)
    {
        return NULL;
    }
    else
    {
        int cellToRemove = findCell(table, key);
        data = table->numOfObject[cellToRemove]->data = NULL;
        table->numOfObject[cellToRemove]->key = NULL;
    }
    return data;
}


/**
 * @brief Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell).
 * If the key was not found, fill both pointers with value of -1.
 * return pointer to the data or null
 */
DataP findData(const TableP table, const void* key, int* arrCell)
{
    DataP pdata = NULL;
    int index = table->hfun(key, (table->tableSize / table->curSize)) * table->curSize;

    for (index; index < (index + table->curSize); index++)
    {
        if (table->fcomp(table->numOfObject[index]->data, key) == 0)
        {
            pdata = table->numOfObject[index]->data;
            arrCell = &index;
        }
    }
    if (arrCell != &index)
    {
        arrCell = (int*)-1;
    }
    return pdata;
}




/**
 * @brief return a pointer to the data that exist in the table in cell number arrCell (where 0 is the
 * first cell).
 * If such data not exist return NULL
 */
DataP getDataAt(const TableP table, int arrCell)
{
    DataP data = NULL;
    if (table != NULL)
    {
        data = table->numOfObject[arrCell];
    }
    return data;
}

/**
 * @brief return the pointer to the key that exist in the table in cell number arrCell (where 0 is the
 * first cell).
 * If such key not exist return NULL
 */
ConstKeyP getKeyAt(const TableP table, int arrCell)
{
    ConstKeyP key = NULL;
    if (table != NULL)
    {
        key = table->numOfObject[arrCell];
    }
    return key;
}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{
    ConstKeyP pkey;
    DataP pdata;

    for (unsigned int i = 0; i < table->tableSize; i++)
    {
        printf("[%d]\t\n", i);
        pdata = table->numOfObject[i]->data;
        pkey = table->numOfObject[i]->key;
        if (table->numOfObject != NULL)
        {
            printf("[%d]\t", i);
            table->printKeyFun(pkey);
            table->printDataFun(pdata);
        }
        printf("\n");
    }
}


/**
 * @brief Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
    void freeTable(TableP table)
    {
        free(table);
    }




#endif // _GENERIC_HASH_TABLE_

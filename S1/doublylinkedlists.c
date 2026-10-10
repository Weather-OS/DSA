/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include <utils.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* WARNING: THE FOLLOWING IMPLEMENTATION IS NOT THREAD SAFE!!! */

typedef struct _SimpleByteArrayNode
{
// PRIVATE:
    BYTE value;
    struct _SimpleByteArrayNode *next;
    struct _SimpleByteArrayNode *previous;
} SimpleByteArrayNode;

typedef struct _SimpleByteArray
{
    SimpleByteArrayNode *head;
    SimpleByteArrayNode *tail;
    size_t size;
} SimpleByteArray;

STATUS SimpleByteArray_init( SimpleByteArray **out_list );
STATUS SimpleByteArray_free( SimpleByteArray *in_list );
STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value );
STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count );
STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed );
STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value );
STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value );

/* initialization */
STATUS SimpleByteArray_init( SimpleByteArray **out_list )
{
    SimpleByteArray *newList = NULL;

    if ( !out_list )
    {
        printf("SimpleByteArray_init: out_list is nullptr!\n");
        return POINTER;
    }

    newList = (SimpleByteArray *)calloc( 1, sizeof(SimpleByteArray) );
    if ( !newList )
    {
        printf("SimpleByteArray_init: failed to allocate list.\n");
        return OUTOFMEMORY;
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    *out_list = newList;

    return SUCCESS;
}

STATUS SimpleByteArray_free( SimpleByteArray *in_list )
{
    SimpleByteArrayNode *current;
    SimpleByteArrayNode *next;

    if ( !in_list )
    {
        printf("SimpleByteArray_free: in_list is nullptr!\n");
        return POINTER;
    }

    current = in_list->head;
    while ( current )
    {
        next = current->next;
        free( current );
        current = next;
    }

    free( in_list );

    return SUCCESS;
}

/* insertion, and removal */
STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value )
{
    SimpleByteArrayNode *newNode = NULL;
    SimpleByteArrayNode *current = NULL;
    size_t iterator;

    if ( !list )
    {
        printf("SimpleByteArray_insert: list is nullptr!\n");
        return POINTER;
    }

    if ( index > list->size )
    {
        printf("SimpleByteArray_insert: out of bounds insertion!\n");
        return BOUNDS;
    }

    newNode = (SimpleByteArrayNode *)malloc( sizeof(*newNode) );
    if ( !newNode )
        return OUTOFMEMORY;

    newNode->value = value;
    newNode->next = NULL;
    newNode->previous = NULL;

    if ( index == 0 )
    {
        //insert at head
        newNode->next = list->head;

        if ( list->head )
            list->head->previous = newNode;
        else
            list->tail = newNode;

        list->head = newNode;
    } else if ( index == list->size )
    {
        // insert at tail
        newNode->previous = list->tail;

        list->tail->next = newNode;
        list->tail = newNode;
    } else
    {
        current = list->head;

        for ( iterator = 0; iterator < index; iterator++ )
            current = current->next;

        newNode->next = current;
        if ( !current )
        {
            printf("SimpleByteArray_insert: catastrophic failure!\n");
            return ERROR;
        }
        newNode->previous = current->previous;

        current->previous->next = newNode;
        current->previous = newNode;
    }

    list->size++;

    return SUCCESS;
}

STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count )
{
    size_t iterator;

    if ( !values || !count )
    {
        printf("SimpleByteArray_insert_bytes: values is nullptr!\n");
        return POINTER;
    }

    for ( iterator = 0; iterator < count; iterator++ )
    {
        RETURN_IF_FAILED( SimpleByteArray_insert( list, index + iterator, values[iterator] ) );
    }

    return SUCCESS;
}

STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed )
{
    SimpleByteArrayNode *current = NULL;
    size_t iterator;

    if ( !list )
    {
        printf("SimpleByteArray_remove: list is nullptr!\n");
        return POINTER;
    }

    if ( list->size <= index )
    {
        printf("SimpleByteArray_remove: out of bounds deletion!\n");
        return BOUNDS;
    }

    current = list->head;

    for (iterator = 0; iterator < index; iterator++)
        current = current->next;

    if ( current->previous )
        current->previous->next = current->next;
    else
        list->head = current->next;

    if ( current->next )
        current->next->previous = current->previous;
    else
        list->tail = current->previous;

    if ( opt_removed )
        *opt_removed = current->value;

    free( current );

    list->size--;

    return SUCCESS;
}

/* getters */
STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value )
{
    SimpleByteArrayNode *current = NULL;
    size_t iterator;

    if ( !list )
    {
        printf("SimpleByteArray_get: list is nullptr!\n");
        return POINTER;
    }

    if ( !list->head || !list->tail )
    {
        printf("SimpleByteArray_get: list is empty!\n");
        return ILLEGAL_METHOD_CALL;
    }

    if ( !value )
    {
        printf("SimpleByteArray_get: value is null!\n");
        return ILLEGAL_METHOD_CALL;
    }

    if ( list->size <= index )
    {
        printf("SimpleByteArray_get: out of bounds fetch!\n");
        return BOUNDS;
    }

    current = list->head;
    for ( iterator = 0; iterator < index; iterator++ )
        current = current->next;

    *value = current->value;

    return SUCCESS;
}

STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value )
{
    if ( !list )
    {
        printf("SimpleByteArray_size: list is nullptr!\n");
        return POINTER;
    }

    if ( !value )
    {
        printf("SimpleByteArray_size: value is null!\n");
        return ILLEGAL_METHOD_CALL;
    }

    *value = list->size;

    return SUCCESS;
}
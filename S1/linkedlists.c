/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include "../include/util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Question 2: Implement a dynamic array with insertion and deletion.
// Create a List type that stores elements in a dynamically allocated linked list.

/* WARNING: THE FOLLOWING IMPLEMENTATION IS NOT THREAD SAFE!!! */

typedef struct _SimpleByteArrayNode
{
// PRIVATE:
    BYTE value;
    struct _SimpleByteArrayNode *next;
} SimpleByteArrayNode;

typedef struct _SimpleByteArray
{
    SimpleByteArrayNode *head;
    SimpleByteArrayNode *tail;
    size_t size;
} SimpleByteArray;

STATUS SimpleByteArray_init( SimpleByteArray *out_list );
STATUS SimpleByteArray_free( SimpleByteArray *in_list );
STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value );
STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count );
STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed );
STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value );
STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value );

/* initialization */
STATUS SimpleByteArray_init( SimpleByteArray *out_list )
{
    if ( !out_list )
    {
        printf("SimpleByteArray_init: out_list is nullptr!\n");
        return POINTER;
    }

    // prevent memory leaks
    if (out_list->head || out_list->tail || out_list->size != 0)
    {
        printf("SimpleByteArray_init: out_list has already been initialized!\n");
        return ILLEGAL_METHOD_CALL;
    }

    out_list->head = NULL;
    out_list->tail = NULL;
    out_list->size = 0;

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

    in_list->size = 0;
    in_list->head = NULL;
    in_list->tail = NULL;

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

    if ( index == list->size )
    {
        // insert at tail
        if ( list->tail )
        {
            list->tail->next = newNode;
            list->tail = newNode;
        } else
        {
            list->head = newNode;
            list->tail = newNode;
        }
    } else if ( index == 0 )
    {
        //insert at head
        newNode->next = list->head;
        list->head = newNode;
    } else
    {
        current = list->head;
        for ( iterator = 1 /* stop right before the dest node*/; iterator < index; iterator++ )
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
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
    SimpleByteArrayNode *removed = NULL;
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

    if ( index == 0 )
    {
        // remove head
        removed = list->head;
        list->head = removed->next;

        if (list->head == NULL)
            list->tail = NULL;
    }
    else
    {
        current = list->head;

        for ( iterator = 1 /* stop right before the dest node*/; iterator < index; iterator++ )
            current = current->next;

        removed = current->next;
        current->next = removed->next;

        if ( removed == list->tail )
            list->tail = current;
    }

    if ( opt_removed )
        *opt_removed = removed->value;

    free( removed );

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
# DSA practice

Build using `cmake -S . -B build && cmake --build build`.  
Run in `build/S1/executable`.

## Session 1

**Arrays and lists**
```c
typedef struct _SimpleByteArray SimpleByteArray;

STATUS SimpleByteArray_init( SimpleByteArray **out_list );
STATUS SimpleByteArray_free( SimpleByteArray *in_list );
STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value );
STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count );
STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed );
STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value );
STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value );
```

We're testing a simple byte array. Bytes can be conformed to other, longer types as well.

### Contiguous lists

`S1/contiguouslists.c`

Involves a contiguous **dynamic** array that grows and shrinks automatically.

| Time Complexity  | Beginning | Arbitrary | Ending |
|------------------|----------:|----------:|-------:|
| Search           | O(1)      | O(1)      | O(1)   |
| Insertion        | O(n)      | O(n)      | O(1)*  |
| Removal          | O(n)      | O(n)      | O(1)** |

*: Could become O(n) if capacity is grown.  
**: Could become O(n) if capacity is shrinked.

### Linked lists

`S1/linkedlists.c`

Involves a linked array.

| Time Complexity  | Beginning | Arbitrary | Ending |
|------------------|----------:|----------:|-------:|
| Search           | O(1)      | O(n)      | O(1)   |
| Insertion        | O(1)      | O(n)      | O(1)   |
| Removal          | O(1)      | O(n)      | O(n)   |

***Both Linked Lists and Contiguous Lists have conforming implementations***

### Tester

`S1/tester.c`

Tests various different aspects of both linked and contiguous lists.  
Outputs tests to `build/S1/ContiguousListsTests(.exe)` and `build/S1/LinkedListsTests(.exe)` respectively.
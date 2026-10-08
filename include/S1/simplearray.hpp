/**
* Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#ifndef DSA_SIMPLEARRAY_HPP
#define DSA_SIMPLEARRAY_HPP

#include "../utils.h"

extern "C" {
typedef struct _SimpleByteArray SimpleByteArray;

extern STATUS SimpleByteArray_init( SimpleByteArray **out_list );
extern STATUS SimpleByteArray_free( SimpleByteArray *in_list );
extern STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value );
extern STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count );
extern STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed );
extern STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value );
extern STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value );
}

template <typename T>
class SimpleArray
{
public:
    SimpleArray()
    {
        // For byte arrays, T needs to be trivially copyable.
        // Things like interfaces, mutated classes or ref counted objects cannot be copied!
        static_assert( std::is_trivially_copyable_v<T> );
        check_st_( SimpleByteArray_init( &m_array ) );
    }

    ~SimpleArray()
    {
        SimpleByteArray_free( m_array );
    }

    void
    Insert( size_t index, T const &value )
    {
        check_st_( SimpleByteArray_insert_bytes( m_array, index * sizeof(T), reinterpret_cast<const BYTE *>(&value), sizeof(T) ) );
    }

    void
    Remove( size_t index )
    {
        size_t iterator;
        const size_t byte_index = index * sizeof(T);

        for ( iterator = 0; iterator < sizeof(T); iterator++ )
            check_st_( SimpleByteArray_remove( m_array, byte_index, nullptr ) );
    }

    T
    Get( size_t index ) const
    {
        T value{};
        size_t iterator;
        const size_t byte_index = index * sizeof(T);
        BYTE* bytes = reinterpret_cast<BYTE*>(&value);

        for ( iterator = 0; iterator < sizeof(T); iterator++ )
            check_st_( SimpleByteArray_get( m_array, byte_index + iterator, &bytes[iterator] ) );

        return value;
    }

    size_t
    Size() const
    {
        size_t byte_size{};
        check_st_( SimpleByteArray_size( m_array, &byte_size ) );

        return byte_size / sizeof(T);
    }

    // push front
    void operator << ( T const &value )
    {
        Insert( 0, value );
    }

private:
    SimpleByteArray *m_array{ nullptr };
};


#endif

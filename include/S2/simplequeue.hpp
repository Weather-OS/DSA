/**
* Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#ifndef DSA_SIMPLEQUEUE_HPP
#define DSA_SIMPLEQUEUE_HPP

#include "S1/simplearray.hpp"

template <typename T>
class SimpleQueue :
    public SimpleArray<T>
{
public:
    SimpleQueue() = default;
    ~SimpleQueue() = default;

    void
    Push( T const &value )
    {
#ifdef LINKED_LISTS
        this->Insert( this->Size(), value );

#elif defined( CONTIGUOUS_LISTS )
        iback++;
        this->Insert( iback, value );
#endif
    }

    T
    Pop()
    {
        T value{};

        if ( this->Size() == 0 )
            throw Exception( STACK_UNDERFLOW );

#ifdef LINKED_LISTS
        value = this->Get( 0 );
        this->Remove( 0 );
        return value;
#elif defined( CONTIGUOUS_LISTS )
        value = this->Get( ifront );

        ifront++;

        if ( ifront > iback )
        {
            ifront = 0;
            iback  = -1;
        }

        return value;
#endif
    }

    T
    Front() const
    {
        if ( this->Size() == 0 )
            throw Exception( STACK_UNDERFLOW );

#ifdef LINKED_LISTS
        return this->Get( 0 );

#elif defined( CONTIGUOUS_LISTS )
        return this->Get( ifront );
#endif
    }

private:
#ifdef CONTIGUOUS_LISTS
    int ifront = 0;
    int iback  = -1;
#endif
};

#endif //DSA_SIMPLEQUEUE_HPP

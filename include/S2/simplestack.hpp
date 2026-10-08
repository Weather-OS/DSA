/**
* Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#ifndef DSA_SIMPLESTACK_HPP
#define DSA_SIMPLESTACK_HPP

template <typename T>
class SimpleStack :
    public SimpleArray<T>
{
public:
    using list = SimpleArray<T>;

    SimpleStack() = default;
    ~SimpleStack() = default;

    T
    Pop()
    {
        T value{};

        if ( this->Size() == 0 )
            throw Exception( STACK_UNDERFLOW );

        value = this->Get( 0 );
        this->Remove( 0 );

        return value;
    }

    void
    Push( T const &value )
    {
        *this << value;
    }

    T
    Top() const
    {
        if ( this->Size() == 0 )
            throw Exception( STACK_UNDERFLOW );

        return this->Get( 0 );
    }
};

#endif //DSA_SIMPLESTACK_HPP

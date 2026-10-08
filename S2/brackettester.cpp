/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include <S1/simplearray.hpp>

// Question 1: Design a simple bracket tester that tests nested brackets.
/*
 * Simple Stack Implementation: */ #include <S2/simplestack.hpp> /*
 */

#include <string>
#include <iostream>
#include <algorithm>

// ---- brackettester.cpp ---- //
int main()
{
    std::string user_input{};
    SimpleStack<BYTE> input{};
    BYTE value{};
    enum class Nest {
        Bracket,
        Parentheses,
        Brace
    };
    SimpleStack<Nest> nest{};

    std::cin >> user_input;

    std::reverse( user_input.begin(), user_input.end() );

    for ( unsigned char c : user_input )
        input.Push( c );

    do
    {
        try
        {
            value = input.Pop();
            if ( value == '(' )
            {
                nest.Push( Nest::Parentheses );
            }
            else if ( value == ')' )
            {
                if ( nest.Size() == 0 || nest.Pop() != Nest::Parentheses )
                {
                    std::printf("NO\n");
                    return 0;
                }
            }
            else if ( value == '{' )
            {
                nest.Push( Nest::Brace );
            }
            else if ( value == '}' )
            {
                if ( nest.Size() == 0 || nest.Pop() != Nest::Brace )
                {
                    std::printf("NO\n");
                    return 0;
                }
            }
            else if ( value == '[' )
            {
                nest.Push( Nest::Bracket );
            }
            else if ( value == ']' )
            {
                if ( nest.Size() == 0 || nest.Pop() != Nest::Bracket )
                {
                    std::printf("NO\n");
                    return 0;
                }
            }
        } catch ( ... )
        {
            std::printf("NO\n");
            return 0;
        }
    } while ( input.Size() > 0 );

    if ( nest.Size() == 0 )
        std::printf("YES\n");
    else
        std::printf("NO\n");

    return 0;
}
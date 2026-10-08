/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include <S1/simplearray.hpp>

// Question 3: Design a program with manual input for a simple queue.
/*
 * Simple Stack Implementation: */ #include <S2/simplestack.hpp> /*
 */
/*
 * Simple Queue Implementation: */ #include <S2/simplequeue.hpp> /*
 */

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

enum class Operation
{
    Enqueue,
    Dequeue,
    Front,
    Size,
    Empty
};

constexpr std::string_view to_string( Operation op )
{
    switch ( op )
    {
        case Operation::Enqueue:
            return "ENQUEUE";
        case Operation::Dequeue:
            return "DEQUEUE";
        case Operation::Front:
            return "FRONT";
        case Operation::Size:
            return "SIZE";
        case Operation::Empty:
            return "EMPTY";
    }
}

int main()
{
    long numOperations;
    SimpleQueue<std::string> queue{};
    SimpleQueue<std::string> results{};
    std::string user_input{};
    std::string operation{};
    std::string value{};
    size_t space_pos;

    std::cin >> user_input;
    numOperations = std::strtol( user_input.c_str(), nullptr, 10 );
    user_input.clear();

    if ( numOperations <= 0 )
        throw Exception( ILLEGAL_METHOD_CALL, "Operations must be a positive integer!\n" );

    do
    {
        numOperations--;

        std::getline( std::cin, user_input );

        space_pos = user_input.find(' ');

        if ( space_pos != std::string::npos )
        {
            operation = user_input.substr( 0, space_pos );
            value = user_input.substr( space_pos + 1 );
        } else
        {
            operation = user_input;
        }

        if ( operation == to_string( Operation::Enqueue ) )
        {
            queue.Push( value );
        } else if ( operation == to_string( Operation::Dequeue ) )
        {
            try
            {
                results.Push( queue.Pop() );
            } catch ( Exception &e )
            {
                results.Push( "EMPTY" );
            }
        } else if ( operation == to_string( Operation::Front ) )
        {
            try
            {
                results.Push( queue.Front() );
            } catch ( Exception &e )
            {
                results.Push( "EMPTY" );
            }
        } else if ( operation == to_string( Operation::Size ) )
        {
            results.Push( std::to_string( queue.Size() ) );
        } else if ( operation == to_string( Operation::Empty ) )
        {
            if ( queue.Size() == 0 )
            {
                results.Push( "YES" );
            } else
            {
                results.Push( "NO" );
            }
        }
    } while ( numOperations >= 0 );

    do
    {
        std::printf("%s\n", results.Pop().c_str() );
    } while ( results.Size() > 0 );

    return 0;
}


/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include <S1/simplearray.hpp>

// Question 4: Design a program with manual input for a simple list.
/*
 * Simple Stack Implementation: */ #include <S2/simplestack.hpp> /*
 */
/*
 * Simple Queue Implementation: */ #include <S2/simplequeue.hpp> /*
 */

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

enum class Operation
{
    Append,
    Insert,
    Delete,
    Get,
    Set,
    Find,
    Size,
    Print
};

constexpr std::string_view to_string( Operation op )
{
    switch ( op )
    {
        case Operation::Append:
            return "APPEND";
        case Operation::Insert:
            return "INSERT";
        case Operation::Delete:
            return "DELETE";
        case Operation::Get:
            return "GET";
        case Operation::Set:
            return "SET";
        case Operation::Find:
            return "FIND";
        case Operation::Size:
            return "SIZE";
        case Operation::Print:
            return "PRINT";
    }
}

int main()
{
    long numOperations;
    long iterator;
    SimpleArray<std::string> list{};
    SimpleQueue<std::string> results{};
    std::string user_input{};
    std::istringstream user_input_stream;
    std::string current_token;

    std::cin >> user_input;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    numOperations = std::strtol( user_input.c_str(), nullptr, 10 );
    user_input.clear();

    if ( numOperations <= 0 )
        throw Exception( ILLEGAL_METHOD_CALL, "Operations must be a positive integer!\n" );

    do
    {
        SimpleArray<std::string> command{};

        std::getline( std::cin, user_input );
        user_input_stream = std::istringstream( user_input );

        while ( user_input_stream >> current_token )
            command.Insert( command.Size(), current_token );

        if ( command.Size() == 0 )
        {
            //malformed command
            numOperations--;
            continue;
        }

        if ( command[0] == to_string( Operation::Append ) )
        {
            try
            {
                list.Insert( list.Size(), command[1].c_str() );
            } catch ( Exception& e )
            {
                throw Exception( e.status, "Failed insertion at " + command[1] );
            }
        } else if ( command[0] == to_string( Operation::Insert ) )
        {
            try
            {
                list.Insert( std::stol( command[1].c_str() ), command[2].c_str() );
            } catch ( ... )
            {
                results.Push( "ERROR" );
            }
        } else if ( command[0] == to_string( Operation::Delete ) )
        {
            try
            {
                results.Push( list.Get( std::stol( command[1].c_str() ) ) );
                list.Remove( std::stol( command[1].c_str() ) );
            } catch ( ... )
            {
                results.Push( "ERROR" );
            }
        } else if ( command[0] == to_string( Operation::Get ) )
        {
            try
            {
                results.Push( list.Get( std::stol( command[1].c_str() ) ) );
            } catch ( ... )
            {
                results.Push( "ERROR" );
            }
        } else if ( command[0] == to_string( Operation::Set ) )
        {
            try
            {
                list.Remove( std::stol( command[1].c_str() ) );
                list.Insert( std::stol( command[1].c_str() ), command[2].c_str() );
            } catch ( ... )
            {
                results.Push( "ERROR" );
            }
        } else if ( command[0] == to_string( Operation::Find ) )
        {
            try
            {
                results.Push( std::to_string( list.Find( command[1].c_str() ) ) );
            } catch ( ... )
            {
                results.Push( "-1" );
            }
        } else if ( command[0] == to_string( Operation::Size ) )
        {
            results.Push( std::to_string( list.Size() ) );
        } else if ( command[0] == to_string( Operation::Print ) )
        {
            std::string output{};
            if ( list.Size() == 0 )
                output = "EMPTY";
            else
                for ( iterator = 0; iterator < list.Size(); iterator++ )
                    output.append( list[iterator] + ' ' );
            results.Push( output );
        }

        numOperations--;
    } while ( numOperations > 0 );

    do
    {
        std::printf("%s\n", results.Pop().c_str() );
    } while ( results.Size() > 0 );

    return 0;
}